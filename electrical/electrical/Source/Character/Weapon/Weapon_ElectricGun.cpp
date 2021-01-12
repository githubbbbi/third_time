#include "DxLib.h"
#include "Weapon_ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"

Weapon_ElectricGun::Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
									   int eraseFrame, bool isCharaLeftWard, int graphHandle):
	WeaponBase(x, y, radius, speedX, speedY, eraseFrame, isCharaLeftWard, graphHandle)
{
	exRate = 1.0;
	aliveTimer = 0;
}

// 移動
void Weapon_ElectricGun::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 左向き
	if ( isLeftWard )
	{
		moveX -= speedX;
	}
	// 右向き
	else
	{
		moveX += speedX;
	}

	moveY += speedY;

	BulletMove();
}

// 消去
void Weapon_ElectricGun::Erase()
{
	// 画面外に出たら消去
	if ( x + radius < 0 ||
		x - radius > MAP_COUNT_X * CHIP_SIZE )
	{
		isAlive = false;
	}

	// マップに当たったら消去
	if ( isMapHit )
	{
		isAlive = false;
	}

	// 一定時間で消去
	aliveTimer++;
	if ( aliveTimer > EG_ALIVE_TIME )
	{
		isAlive = false;
	}
	else if ( aliveTimer > EG_ALIVE_TIME / 2 )
	{
		// 小さくなる
		if ( exRate > 0.0 )
		{
			exRate -= 0.05;
		}
	}
}

// 更新処理
void Weapon_ElectricGun::Update()
{
	Move();
	Erase();
}

// 描画処理
void Weapon_ElectricGun::Draw(int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
					  exRate, 0.0, graphHandle, true, isLeftWard);
	}
}