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
	this->isCharaLeftWard = isCharaLeftWard;
	this->graphHandle = graphHandle;

	moveY = 0.0f;
	exRate = 1.0;

	// ������
	if ( isCharaLeftWard )
	{
		moveX = -speed;
	}
	// �E����
	else
	{
		moveX = speed;
	}

	hitFrame = 0;
	aliveTimer = 0;
	isAlive = true;
	isMapHit = false;
}

// �}�b�v�Ƃ̓����蔻����l�������ړ�
void ElectricGun::Move()
{
	// �_�~�[ �����X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	static float dummy = 0.0f;

	// �����蔻����s������
	static int hitLength = radius - 10;

	// �㉺�ړ��ʂ�������
	y += moveY;

	// ���E�̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - hitLength, y + hitLength, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitLength, y + hitLength, &moveX, &dummy);	// �E��
	Utility::MapHitCheck(x - hitLength, y - hitLength, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitLength, y - hitLength, &moveX, &dummy);	// �E��

	// �ړ��ʂ�speed�Ɠ������Ȃ��ꍇ�}�b�v�q�b�g
	// ������
	if ( isCharaLeftWard )
	{
		if ( moveX != -speed )
		{
			hitFrame++;
		}
	}
	// �E����
	else
	{
		if ( moveX != speed )
		{
			hitFrame++;
		}
	}

	// �q�b�g��2�t���[���o�߂Œe������
	if ( hitFrame > 2 )
	{
		isMapHit = true;
	}

	// ���E�ړ��ʂ�������
	x += moveX;
}

// ����
void ElectricGun::Erase()
{
	// ��ʊO�ɏo�������
	if ( x + radius < 0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}

	// �}�b�v�ɓ������������
	if ( isMapHit )
	{
		isAlive = false;
	}

	// ��莞�Ԃŏ���
	aliveTimer++;
	if ( aliveTimer > ALIVE_TIME )
	{
		isAlive = false;
	}
	else if ( aliveTimer > ALIVE_TIME / 2 )
	{
		// �������Ȃ�
		if ( exRate > 0.0 )
		{
			exRate -= 0.05;
		}
	}
}

// �X�V����
void ElectricGun::Update()
{
	Move();
	Erase();
}

// �`�揈��
void ElectricGun::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y,
					  exRate, 0.0, graphHandle, true);
	}

	DrawFormatString(0, 120, GetColor(255, 255, 255), "hitFrame:%d", hitFrame);
}

// �e���q�b�g�����ꍇ�̏���
void ElectricGun::Hit()
{
	isAlive = false;
}

// X���W���擾
float ElectricGun::GetPosX()
{
	return x;
}

// Y���W���擾
float ElectricGun::GetPosY()
{
	return y;
}

// ���a���擾
int ElectricGun::GetRadius()
{
	return radius;
}

bool ElectricGun::GetIsAlive()
{
	return isAlive;
}