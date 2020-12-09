#include "CharaBase.h"

// コンストラクタ
CharaBase::CharaBase(int x, int y, int radius,
					 int speed, int hp, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->graphHandle = graphHandle;

	this->hp = hp;

	moveX = 0;
	moveY = 0;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
}

// X座標を取得
int CharaBase::GetPosX()
{
	return x;
}

// Y座標を取得
int CharaBase::GetPosY()
{
	return y;
}

// 半径を取得
int CharaBase::GetRadius()
{
	return radius;
}

// 画像の向きを変化
void CharaBase::ChangeGraphicDirection()
{
	// 左に進行
	if ( moveX < 0 )
	{
		isLeftWard = true;
	}
	// 右に進攻
	else if ( moveX > 0 )
	{
		isLeftWard = false;
	}
}