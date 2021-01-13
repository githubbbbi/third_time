#include "DxLib.h"
#include "Weapon_WaterGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"

const float WG_GRAVITY = 0.85f;

Weapon_WaterGun::Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
								 int eraseFrame, bool isCharaLeftWard, int graphHandle):
	WeaponBase(x, y, radius, speedX, speedY, eraseFrame, isCharaLeftWard, graphHandle)
{
	moveY = -10.0f;
}

// ブロックとの当たり判定を考慮した移動
void Weapon_WaterGun::Move()
{
	// 移動量初期化
	moveX = 0.0f;

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
void Weapon_WaterGun::Erase()
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
}

// 更新処理
void Weapon_WaterGun::Update()
{
	Move();
	Erase();
}

// 描画処理
void Weapon_WaterGun::Draw(int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
	}
}