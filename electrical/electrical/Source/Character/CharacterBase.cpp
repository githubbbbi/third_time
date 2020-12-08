#include "CharacterBase.h"

// コンストラクタ
CharacterBase::CharacterBase(int x, int y, int speed,
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