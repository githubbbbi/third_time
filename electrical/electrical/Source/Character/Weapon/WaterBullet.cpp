#include "DxLib.h"
#include "WaterBullet.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"

WaterBullet::WaterBullet(float x, float y, int radius, float speed, bool isCharaLeftWard, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->isLeftWard = isCharaLeftWard;
	this->graphHandle = graphHandle;

	moveY = -8.0f;
	exRate = 1.0;

	// ������
	if (isLeftWard)
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

// �u���b�N�Ƃ̓����蔻����l�������ړ�
void WaterBullet::Move()
{
	// �_�~�[ �����X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	static float dummy = 0.0f;

	// �����蔻����s������
	static int hitLength = radius - 10;

	// 1�t���[���O��moveY�̒l��ۑ�
	float oldMoveY = moveY + 0.85f;

	// �d�͗���
	moveY += 0.85f;

	// �O��̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - hitLength, y + hitLength, &dummy, &moveY);	// ����
	Utility::MapHitCheck(x + hitLength, y + hitLength, &dummy, &moveY);	// �E��
	Utility::MapHitCheck(x - hitLength, y - hitLength, &dummy, &moveY);	// ����
	Utility::MapHitCheck(x + hitLength, y - hitLength, &dummy, &moveY);	// �E��

	// �ړ��ʂ��������Ȃ��Ƃ��Ƀ}�b�v�q�b�g
	if (moveY != oldMoveY)
	{
		hitFrame++;
	}

	// ���E�̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - hitLength, y + hitLength, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitLength, y + hitLength, &moveX, &dummy);	// �E��
	Utility::MapHitCheck(x - hitLength, y - hitLength, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitLength, y - hitLength, &moveX, &dummy);	// �E��

	// �ړ��ʂ�speed�Ɠ������Ȃ��ꍇ�}�b�v�q�b�g
	// ������
	if (isLeftWard)
	{
		if (moveX != -speed)
		{
			hitFrame++;
		}
	}
	// �E����
	else
	{
		if (moveX != speed)
		{
			hitFrame++;
		}
	}

	// �q�b�g��2�t���[���o�߂Œe������
	if (hitFrame > 1)
	{
		isMapHit = true;
	}

	// �㉺�ړ��ʂ�������
	y += moveY;

	// ���E�ړ��ʂ�������
	x += moveX;
}

// ����
void WaterBullet::Erase()
{
	// ��ʊO�ɏo�������
	if (x + radius < 0 ||
		x - radius > MAP_COUNT_X * CHIP_SIZE)
	{
		isAlive = false;
	}

	// �}�b�v�ɓ������������
	if (isMapHit)
	{
		isAlive = false;
	}

	//// ��莞�Ԃŏ���
	//aliveTimer++;
	//if (aliveTimer > ALIVE_TIME)
	//{
	//	isAlive = false;
	//}
	//else if (aliveTimer > ALIVE_TIME / 2)
	//{
	//	// �������Ȃ�
	//	if (exRate > 0.0)
	//	{
	//		exRate -= 0.05;
	//	}
	//}
}

// �X�V����
void WaterBullet::Update()
{
	Move();
	Erase();
}

// �`�揈��
void WaterBullet::Draw(int scrollX, int scrollY)
{
	if (isAlive)
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
			exRate, 0.0, graphHandle, true, isLeftWard);
	}
}

// �e���q�b�g�����ꍇ�̏���
void WaterBullet::Hit()
{
	isAlive = false;
}

// X���W���擾
float WaterBullet::GetPosX()
{
	return x;
}

// Y���W���擾
float WaterBullet::GetPosY()
{
	return y;
}

// ���a���擾
int WaterBullet::GetRadius()
{
	return radius;
}

// isAlive���擾
bool WaterBullet::GetIsAlive()
{
	return isAlive;
}
