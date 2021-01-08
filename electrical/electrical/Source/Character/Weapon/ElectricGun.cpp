#include "DxLib.h"
#include "ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"

ElectricGun::ElectricGun(float x, float y, int radius,
						 float speed, bool isCharaLeftWard, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->isLeftWard = isCharaLeftWard;
	this->graphHandle = graphHandle;

	moveY = 0.0f;
	exRate = 1.0;

	// 左向き
	if ( isLeftWard )
	{
		moveX = -speed;
	}
	// 右向き
	else
	{
		moveX = speed;
	}

	hitFrame = 0;
	aliveTimer = 0;
	isAlive = true;
	isMapHit = false;
}

// マップとの当たり判定を考慮した移動
void ElectricGun::Move()
{
	// ダミー これはXまたはY方向の移動量について考慮しない場合に用いる
	static float dummy = 0.0f;

	// 当たり判定を行う長さ
	static int hitLength = radius - 10;

	// 上下移動量を加える
	y += moveY;

	// 左右の移動量をチェック
	Utility::MapHitCheck(x - hitLength, y + hitLength, &moveX, &dummy);	// 左下
	Utility::MapHitCheck(x + hitLength, y + hitLength, &moveX, &dummy);	// 右下
	Utility::MapHitCheck(x - hitLength, y - hitLength, &moveX, &dummy);	// 左上
	Utility::MapHitCheck(x + hitLength, y - hitLength, &moveX, &dummy);	// 右上

	// 移動量がspeedと等しくない場合マップヒット
	// 左向き
	if ( isLeftWard )
	{
		if ( moveX != -speed )
		{
			hitFrame++;
		}
	}
	// 右向き
	else
	{
		if ( moveX != speed )
		{
			hitFrame++;
		}
	}

	// ヒット後2フレーム経過で弾を消去
	if ( hitFrame > 2 )
	{
		isMapHit = true;
	}

	// 左右移動量を加える
	x += moveX;
}

// 消去
void ElectricGun::Erase()
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
	if ( aliveTimer > ALIVE_TIME )
	{
		isAlive = false;
	}
	else if ( aliveTimer > ALIVE_TIME / 2 )
	{
		// 小さくなる
		if ( exRate > 0.0 )
		{
			exRate -= 0.05;
		}
	}
}

// 更新処理
void ElectricGun::Update()
{
	Move();
	Erase();
}

// 描画処理
void ElectricGun::Draw(int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
					  exRate, 0.0, graphHandle, true, isLeftWard);
	}
}

// 弾がヒットした場合の処理
void ElectricGun::Hit()
{
	isAlive = false;
}

// X座標を取得
float ElectricGun::GetPosX()
{
	return x;
}

// Y座標を取得
float ElectricGun::GetPosY()
{
	return y;
}

// 半径を取得
int ElectricGun::GetRadius()
{
	return radius;
}

bool ElectricGun::GetIsAlive()
{
	return isAlive;
}