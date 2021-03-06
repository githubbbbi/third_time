#include "DxLib.h"
#include "Weapon_WaterGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../..//Resource/Graphic.h"
#include "../..//Resource/Sound_SE.h"

const float WG_GRAVITY = 0.85f;

Weapon_WaterGun::Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
								 float flightDistance, int eraseFrame, bool isCharaLeft):
	WeaponBase(x, y, radius, speedX, speedY, flightDistance, eraseFrame, isCharaLeft)
{
	moveY = -10.0f;

	// SE再生
	Sound_SE::GetInstance()->PlaySE(e_SHOT_WATER_GUN_SE, true);
}

// ブロックとの当たり判定を考慮しない移動
void Weapon_WaterGun::Move()
{
	// 移動量初期化
	moveX = 0.0f;

	// 左向き
	if ( isLeft )
	{
		moveX -= speedX;
	}
	// 右向き
	else
	{
		moveX += speedX;
	}

	moveY += speedY;

	// 飛距離は無限
	flightDistance -= 0.0f;

	BulletMove(false);
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
}

// 更新処理
void Weapon_WaterGun::Update()
{
	Move();
	Erase();
}

// 描画処理
void Weapon_WaterGun::Draw(int scrollX, int scrollY,
						   int displaceX, int displaceY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX + displaceX,
					  (int)y - scrollY + displaceY,
					  0.75, 0.0, Graphic::GetInstance()->GetWaterGun(), true, isLeft);
	}
}