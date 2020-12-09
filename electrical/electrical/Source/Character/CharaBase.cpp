#include "CharaBase.h"

// コンストラクタ
CharaBase::CharaBase(int x, int y, int speed,
					 int radius, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->graphHandle = graphHandle;

	moveX = 0;
	moveY = 0;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
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