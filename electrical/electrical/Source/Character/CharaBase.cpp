#include "CharaBase.h"

// �R���X�g���N�^
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

// X���W���擾
int CharaBase::GetPosX()
{
	return x;
}

// Y���W���擾
int CharaBase::GetPosY()
{
	return y;
}

// ���a���擾
int CharaBase::GetRadius()
{
	return radius;
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