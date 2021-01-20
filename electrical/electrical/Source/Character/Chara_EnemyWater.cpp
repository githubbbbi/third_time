#include "DxLib.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EW_WIDTH = 50;
const int EW_HEIGHT = 50;
const int EW_BULLET_INTERVAL = 70;
const int EW_MOTION[e_EW_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 }
};

Chara_EnemyWater::Chara_EnemyWater(float x, float y, int radius, int width, int height,
								   float speed, int hp, int attackPower):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower)
{
	bulletInterval = 0;
	bulletSpeed = 0.0f;
}

Chara_EnemyWater::~Chara_EnemyWater()
{
	// 水弾
	for ( int i = waterGun.size() - 1; i >= 0; i-- )
	{
		delete waterGun[i];
		waterGun.erase(waterGun.begin() + i);
	}
}

// 初期化処理
void Chara_EnemyWater::Initialize()
{

}

// 移動
void Chara_EnemyWater::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// 向きを変更
void Chara_EnemyWater::ChangeDirection(float playerX)
{
	if ( x == playerX )
	{
		return;
	}

	if ( x > playerX )
	{
		// 左を向く
		isLeftWard = true;
	}
	else
	{
		// 右を向く
		isLeftWard = false;
	}
}

// 状態
void Chara_EnemyWater::State()
{
	// 待機
	if ( moveX == 0.0f && moveY == 0.0f )
	{
		state = e_EW_STATE_IDLE;
	}

	// 攻撃
	if ( isAttack )
	{
		state = e_EW_STATE_ATTACK;
	}

	// ダメーを受ける(色点滅中)
	if ( isCBlinking )
	{
		state = e_EW_STATE_RECIEVE_DAMAGE;
	}
}

// 更新処理
void Chara_EnemyWater::Update(float playerX, float playerY)
{
	if ( isAlive )
	{
		Move();
		ChangeDirection(playerX);
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		LocalAnimation(EW_MOTION, 0.0f);
	}

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyWater::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// 水弾
	for ( unsigned int i = 0; i < waterGun.size(); i++ )
	{
		waterGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyWater(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 攻撃ヒット
void Chara_EnemyWater::HitAttack(int index)
{
	waterGun[index]->Hit();
}

// 武器処理管理
void Chara_EnemyWater::WeaponManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// 弾のインターバルを測るカウント
	bulletInterval++;

	// インターバルの初期化
	if ( bulletInterval > EW_BULLET_INTERVAL || isCBlinking )
	{
		bulletInterval = 0;
	}

	// 生成
	if ( bulletInterval == EW_BULLET_INTERVAL )
	{
		double a = (double)x - playerX;
		double b = (double)y - playerY;
		double distance = sqrt(a * a + b * b);

		//　プレイヤーと敵の距離によって、弾のスピードを変更する
		if ( distance > 500 )
		{
			bulletSpeed = 15.0f;
		}
		else if ( distance > 300 )
		{
			bulletSpeed = 10.0f;
		}
		else
		{
			bulletSpeed = 5.0f;
		}

		int xx = 16;
		if ( isLeftWard )
		{
			xx *= -1;
		}

		waterGun.push_back(new Weapon_WaterGun(x + xx, y + 8, 16,
											   bulletSpeed,
											   GRAVITY, 0,
											   isLeftWard));

		isAttack = true;
	}

	// 水弾
	for ( unsigned int i = 0; i < waterGun.size(); i++ )
	{
		waterGun[i]->Update();
	}

	// 水弾削除
	for ( int i = waterGun.size() - 1; i >= 0; i-- )
	{
		if ( !waterGun[i]->GetIsAlive() )
		{
			delete waterGun[i];
			waterGun.erase(waterGun.begin() + i);
		}

	}
}

// 水弾の要素数
unsigned int Chara_EnemyWater::GetGunSize()
{
	return waterGun.size();
}

// 水弾のX座標取得
float Chara_EnemyWater::GetGunPosX(int index)
{
	return waterGun[index]->GetPosX();
}

// 水弾のY座標取得
float Chara_EnemyWater::GetGunPosY(int index)
{
	return waterGun[index]->GetPosY();
}

// 水弾のradius取得
int Chara_EnemyWater::GetGunRadius(int index)
{
	return waterGun[index]->GetRadius();
}

// 水銃のisLeftWard取得
bool Chara_EnemyWater::GetIsGunLeftWard(int index)
{
	return waterGun[index]->GetIsLeftWard();
}