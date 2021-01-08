#include "DxLib.h"
#include "Chara_EnemyGun.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"

Chara_EnemyGun::Chara_EnemyGun(float x, float y, int radius, int width, int height,
							   float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
{
	shotBulletNum = 0;
	bulletInterval = 0;
	isTargetLock = false;
}

Chara_EnemyGun::~Chara_EnemyGun()
{
	// 電気銃
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// 初期化処理
void Chara_EnemyGun::Initialize()
{

}

void Chara_EnemyGun::Move(float playerX, float playerY, bool isPlayerAlive)
{
	// 初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 進行方向チェンジ
	ChangeDirection();

	// 射程内で止まる 間にブロックがあればとまらない
	if ( playerX - x + radius >= 200 ||
		x - radius - playerX >= 200 || IsBlock(playerX) )
	{
		moveX += speed;

		// 射程外では撃たない
		isTargetLock = false;

		// ジャンプ
		Jump();

	}
	// ｙが違う場合なら、射程内でも進む
	else if ( y != playerY )
	{
		moveX += speed;

		// ジャンプ
		Jump();
	}
	else
	{
		// 射程内で、y座標が同じなら撃つ
		isTargetLock = true;
	}

	// 標的になったら、プレイヤーを追いかける（反転したり）
	if ( isTargetLock )
	{
		// プレイヤーより右で、右を向いている場合、左向きに変える
		if ( playerX < x && speed > 0 )
		{
			speed *= -1;
			isLeftWard = TRUE;
		}
		else if ( playerX > x && speed < 0 )
		{
			speed *= -1;
			isLeftWard = FALSE;
		}
	}

	CharaMove((float)width, (float)height);
}

// 更新処理
void Chara_EnemyGun::Update(float playerX, float playerY, bool isPlayerAlive,
							float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 2);
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyGun::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
		SetDrawBright(255, 255, 255);
	}
}

// 攻撃ヒット
void Chara_EnemyGun::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// 攻撃処理の管理
void Chara_EnemyGun::WeaponManager(int electricGunGH)
{
	// 弾のインターバルを測るカウント
	bulletInterval++;

	// インターバルの初期化
	if ( bulletInterval > BULLET_INTERVAL )
	{
		bulletInterval = 0;
	}

	// 生成
	if ( bulletInterval == BULLET_INTERVAL && isTargetLock )
	{
		electricGun.push_back(new ElectricGun(x, y,
											  16, 10.0f,
											  isLeftWard,
											  electricGunGH));
	}

	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Update();
	}

	// 電気銃削除
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		if ( !electricGun[i]->GetIsAlive() )
		{
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}

	}
}

// 電気銃の要素数
unsigned int Chara_EnemyGun::GetGunSize()
{
	return electricGun.size();
}

// 電気銃のX座標取得
float Chara_EnemyGun::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// 電気銃のY座標取得
float Chara_EnemyGun::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// 電気銃のradius取得
int Chara_EnemyGun::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}