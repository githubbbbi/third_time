#include "DxLib.h"
#include "Weapon_ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../..//Resource/Graphic.h"

const float EG_SPEED = 10.0f;
const int EG_ALIVE_TIME = 30;

Weapon_ElectricGun::Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
									   int eraseFrame, bool isCharaLeftWard):
	WeaponBase(x, y, radius, speedX, speedY, eraseFrame, isCharaLeftWard)
{
	exRate = 1.0;
	aliveTimer = 0;
}

// �ړ�
void Weapon_ElectricGun::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;
	moveY = 0.0f;

	// ������
	if ( isLeftWard )
	{
		moveX -= speedX;
	}
	// �E����
	else
	{
		moveX += speedX;
	}

	moveY += speedY;

	BulletMove();
}

// ����
void Weapon_ElectricGun::Erase()
{
	// ��ʊO�ɏo�������
	if ( x + radius < 0 ||
		x - radius > MAP_COUNT_X * CHIP_SIZE )
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
	if ( aliveTimer > EG_ALIVE_TIME )
	{
		isAlive = false;
	}
	else if ( aliveTimer > EG_ALIVE_TIME / 2 )
	{
		// �������Ȃ�
		if ( exRate > 0.0 )
		{
			exRate -= 0.05;
		}
	}
}

// �X�V����
void Weapon_ElectricGun::Update()
{
	Move();
	Erase();
}

// �`�揈��
void Weapon_ElectricGun::Draw(int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
					  exRate, 0.0, Graphic::GetInstance()->GetElectricGun(), true, isLeftWard);
	}
}