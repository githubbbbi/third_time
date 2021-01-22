#include "WeaponBase.h"
#include "../../Utility/Utility.h"

WeaponBase::WeaponBase(float x, float y, int radius, float speedX, float speedY,
					   int eraseFrame, bool isCharaLeftWard)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speedX = speedX;
	this->speedY = speedY;
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

// �}�b�v�`�b�v�Ƃ̓����蔻��
void WeaponBase::BulletMove(bool isHitCalc)
{
	// �_�~�[
	float dummy = 0.0f;

	// �����蔻����s������
	int hitLength = radius - 10;

	// 1�t���[���O�̍��W���擾
	oldX = x;
	oldY = y;

	if ( isHitCalc )
	{
		// �㉺�̈ړ��ʂ��`�F�b�N
		Utility::MapHitCheck(x - hitLength, y + hitLength, &dummy, &moveY);	// ����
		Utility::MapHitCheck(x + hitLength, y + hitLength, &dummy, &moveY);	// �E��
		Utility::MapHitCheck(x - hitLength, y - hitLength, &dummy, &moveY);	// ����
		Utility::MapHitCheck(x + hitLength, y - hitLength, &dummy, &moveY);	// �E��
	}

	// �㉺�ړ��ʂ�������
	y += moveY;

	if ( isHitCalc )
	{
		// ���E�̈ړ��ʂ��`�F�b�N
		Utility::MapHitCheck(x - hitLength, y + hitLength, &moveX, &dummy);	// ����
		Utility::MapHitCheck(x + hitLength, y + hitLength, &moveX, &dummy);	// �E��
		Utility::MapHitCheck(x - hitLength, y - hitLength, &moveX, &dummy);	// ����
		Utility::MapHitCheck(x + hitLength, y - hitLength, &moveX, &dummy);	// �E��
	}

	// ���E�ړ��ʂ�������
	x += moveX;

	if ( isHitCalc )
	{
		// 1�t���[���O�̍��W�Ɠ������ꍇ�}�b�v�q�b�g
		// X���W
		if ( speedX != 0.0f && x == oldX )
		{
			mapHitFrame++;
		}
		// Y���W
		else if ( speedY != 0.0f && y == oldY )
		{
			mapHitFrame++;
		}

		// �q�b�g��X�t���[���o�߂Œe������
		if ( mapHitFrame > eraseFrame )
		{
			isMapHit = true;
		}
	}
}

// �e���q�b�g�����ꍇ�̏���
void WeaponBase::Hit()
{
	isAlive = false;
}

// X���W���擾
float WeaponBase::GetPosX()
{
	return x;
}

// Y���W���擾
float WeaponBase::GetPosY()
{
	return y;
}

// ���a���擾
int WeaponBase::GetRadius()
{
	return radius;
}

bool WeaponBase::GetIsAlive()
{
	return isAlive;
}

// isLeftWard���擾
bool WeaponBase::GetIsLeftWard()
{
	return isLeftWard;
}