#include "DxLib.h"
#include "Weapon_ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../../Resource/Graphic.h"
#include "../../Resource/Sound_SE.h"

const float EG_SPEED = 10.0f;
const int EG_ALIVE_TIME = 30;

Weapon_ElectricGun::Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
									   int eraseFrame, bool isCharaLeftWard):
	WeaponBase(x, y, radius, speedX, speedY, eraseFrame, isCharaLeftWard)
{
	exRate = 0.75;
	aliveTimer = 0;

	// SE再生
	Sound_SE::GetInstance()->PlaySE(e_SHOT_ELECTRIC_GUN_SE, false);
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

	BulletMove(true);
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
					  exRate, 0.0, Graphic::GetInstance()->GetElectricGun(), true, isLeftWard);
	}
}