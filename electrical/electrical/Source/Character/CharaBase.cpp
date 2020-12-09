#include "CharaBase.h"

// �R���X�g���N�^
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

// �摜�̌�����ω�
void CharaBase::ChangeGraphicDirection()
{
	// ���ɐi�s
	if ( moveX < 0 )
	{
		isLeftWard = true;
	}
	// �E�ɐi�U
	else if ( moveX > 0 )
	{
		isLeftWard = false;
	}
}