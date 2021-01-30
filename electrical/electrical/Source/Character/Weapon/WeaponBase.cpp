#include "WeaponBase.h"
#include "../../Utility/Utility.h"

WeaponBase::WeaponBase(float x, float y, int radius, float speedX, float speedY,
					   float flightDistance, int eraseFrame, bool isCharaLeftWard)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speedX = speedX;
	this->speedY = speedY;
	this->flightDistance = flightDistance;
	this->eraseFrame = eraseFrame;
	this->isLeftWard = isCharaLeftWard;

	oldX = x;
	oldY = y;

	moveX = 0.0f;
	moveY = 0.0f;

	mapHitFrame = 0;
	isAlive = true;
	isMapHit = false;
}

// マップチップとの当たり判定
void WeaponBase::BulletMove(bool isHitCalc)
{
	// ダミー
	float dummy = 0.0f;

	// 当たり判定を行う長さ
	int hitLength = radius - 10;

	// 1フレーム前の座標を取得
	oldX = x;
	oldY = y;

	if ( isHitCalc )
	{
		// 上下の移動量をチェック
		Utility::MapHitCheck(x - hitLength, y + hitLength, &dummy, &moveY);	// 左下
		Utility::MapHitCheck(x + hitLength, y + hitLength, &dummy, &moveY);	// 右下
		Utility::MapHitCheck(x - hitLength, y - hitLength, &dummy, &moveY);	// 左上
		Utility::MapHitCheck(x + hitLength, y - hitLength, &dummy, &moveY);	// 右上
	}

	// 上下移動量を加える
	y += moveY;

	if ( isHitCalc )
	{
		// 左右の移動量をチェック
		Utility::MapHitCheck(x - hitLength, y + hitLength, &moveX, &dummy);	// 左下
		Utility::MapHitCheck(x + hitLength, y + hitLength, &moveX, &dummy);	// 右下
		Utility::MapHitCheck(x - hitLength, y - hitLength, &moveX, &dummy);	// 左上
		Utility::MapHitCheck(x + hitLength, y - hitLength, &moveX, &dummy);	// 右上
	}

	// 左右移動量を加える
	x += moveX;

	if ( isHitCalc )
	{
		// 1フレーム前の座標と等しい場合マップヒット
		// X座標
		if ( speedX != 0.0f && x == oldX )
		{
			mapHitFrame++;
		}
		// Y座標
		else if ( speedY != 0.0f && y == oldY )
		{
			mapHitFrame++;
		}

		// ヒット後Xフレーム経過で弾を消去
		if ( mapHitFrame > eraseFrame )
		{
			isMapHit = true;
		}
	}
}

// 弾がヒットした場合の処理
void WeaponBase::Hit()
{
	isAlive = false;
}

// X座標を取得
float WeaponBase::GetPosX()
{
	return x;
}

// Y座標を取得
float WeaponBase::GetPosY()
{
	return y;
}

// 半径を取得
int WeaponBase::GetRadius()
{
	return radius;
}

bool WeaponBase::GetIsAlive()
{
	return isAlive;
}

// isLeftWardを取得
bool WeaponBase::GetIsLeftWard()
{
	return isLeftWard;
}