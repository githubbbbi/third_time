#include "DxLib.h"
#include "Weapon_WaterGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../..//Resource/Graphic.h"

const float WG_GRAVITY = 0.85f;

Weapon_WaterGun::Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
								 int eraseFrame, bool isCharaLeftWard):
	WeaponBase(x, y, radius, speedX, speedY, eraseFrame, isCharaLeftWard)
{
	moveY = -10.0f;
}

// �u���b�N�Ƃ̓����蔻����l�������ړ�
void Weapon_WaterGun::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;

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
void Weapon_WaterGun::Erase()
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
}

// �X�V����
void Weapon_WaterGun::Update()
{
	Move();
	Erase();
}

// �`�揈��
void Weapon_WaterGun::Draw(int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
					  1.0, 0.0, Graphic::GetWaterGun(), true, isLeftWard);
	}
}