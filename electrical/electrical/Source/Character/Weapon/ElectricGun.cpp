#include "DxLib.h"
#include "ElectricGun.h"
#include "../../Define/Define.h"

ElectricGun::ElectricGun(float x, float y, int radius,
						 float speed, bool isCharaLeftWard, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->isCharaLeftWard = isCharaLeftWard;
	this->graphHandle = graphHandle;

	isAlive = true;
}

// 更新処理
void ElectricGun::Update()
{
	// 左向き
	if ( isCharaLeftWard )
	{
		x -= speed;
	}
	// 右向き
	else
	{
		x += speed;
	}

	// 画面外に出たら削除
	if ( x + radius < 0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}
}

// 描画処理
void ElectricGun::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y,
					  1.0, 0.0, graphHandle, true);
	}
}

// 弾がヒットした場合の処理
void ElectricGun::BulletHit()
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