#include "DxLib.h"
#include "Weapon_ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../../Resource/Graphic.h"
#include "../../Resource/Sound_SE.h"

const float EG_SPEED = 10.0f;

Weapon_ElectricGun::Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
									   float flightDistance, int eraseFrame, bool isCharaLeftWard):
	WeaponBase(x, y, radius, speedX, speedY, flightDistance, eraseFrame, isCharaLeftWard)
{
	exRate = 0.75;

	// SE�Đ�
	Sound_SE::GetInstance()->PlaySE(e_SHOT_ELECTRIC_GUN_SE, false);
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

	flightDistance -= fabsf(moveX);

	BulletMove(true);
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

	// �򋗗�
	if ( flightDistance <= 0.0f )
	{
		exRate -= 0.05f;
		// �������Ȃ��������
		if ( exRate < 0.0f )
		{
			isAlive = false;
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