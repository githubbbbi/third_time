#include "DxLib.h"
#include <algorithm>
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
								   float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
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

// 移動
void Chara_EnemyWater::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// 武器処理管理
void Chara_EnemyWater::WeaponManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// 弾のインターバルを測るカウント
	if ( isAlive )
	{
		bulletInterval++;
	}

	// インターバルの初期化
	if ( bulletInterval > EW_BULLET_INTERVAL || isCBlinking )
	{
		bulletInterval = 0;
	}

	// 生成
	if ( bulletInterval == EW_BULLET_INTERVAL )
	{
		double a = (double)x - playerX;
		double distance = sqrt(a * a);

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

		// 生成座標
		float xx = 24.0f;
		if ( isLeft )
		{
			xx *= -1.0f;
		}

		// 飛距離
		float flightDistance = 100.0f;
		waterGun.push_back(new Weapon_WaterGun(x + xx, y + 8.0f,
											   16,
											   bulletSpeed, GRAVITY,
											   flightDistance, 0,
											   isLeft));

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
			// 攻撃座標をリセット
			attackX = 0.0f;
			attackY = 0.0f;

			delete waterGun[i];
			waterGun.erase(waterGun.begin() + i);
		}
	}
}

// 攻撃管理
void Chara_EnemyWater::AttackManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// プレイヤーと一番距離が近いものを並べ替え、先頭にもってくる
	std::sort(waterGun.begin(), waterGun.end(),
			  [playerX, playerY](Weapon_WaterGun *a, Weapon_WaterGun *b)
	{
		return fabsf(playerX - a->GetPosX()) < fabsf(playerX - b->GetPosX()) &&
			fabsf(playerY - a->GetPosY()) < fabsf(playerY - b->GetPosY());
	});

	if ( waterGun.size() <= 0 )
	{
		return;
	}

	attackX = waterGun[0]->GetPosX();;
	attackY = waterGun[0]->GetPosY();;
	attackRadius = waterGun[0]->GetRadius();
	isAttackLeft = waterGun[0]->GetIsLeft();
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
		isLeft = true;
	}
	else
	{
		// 右を向く
		isLeft = false;
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
void Chara_EnemyWater::Update(float playerX, float playerY,
							  int screenX, int screenY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move();
		ChangeDirection(playerX);
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EW_MOTION, 0.0f, 0.0f);
	}

	WeaponManager(playerX, playerY, isPlayerAlive);
	AttackManager(playerX, playerY, isPlayerAlive);

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyWater::Draw(float shakeX, float shakeY,
							int scrollX, int scrollY)
{
	// 水弾
	for ( unsigned int i = 0; i < waterGun.size(); i++ )
	{
		waterGun[i]->Draw(scrollX, scrollY, displaceX, displaceY);
	}

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX + displaceX,
					  (int)(y + shakeY) - scrollY + displaceY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyWater(graphIndex), true, isLeft);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 攻撃ヒット
void Chara_EnemyWater::HitAttack()
{
	if ( waterGun.size() <= 0 )
	{
		return;
	}

	waterGun[0]->Hit();
}