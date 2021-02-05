#include "DxLib.h"
#include "Weapon_WaterGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../..//Resource/Graphic.h"
#include "../..//Resource/Sound_SE.h"

const float WG_GRAVITY = 0.85f;

Weapon_WaterGun::Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
								 float flightDistance, int eraseFrame, bool isCharaLeft):
	WeaponBase(x, y, radius, speedX, speedY, flightDistance, eraseFrame, isCharaLeft)
{
	moveY = -10.0f;

	// SE�Đ�
	Sound_SE::GetInstance()->PlaySE(e_SHOT_WATER_GUN_SE, true);
}

// �u���b�N�Ƃ̓����蔻����l�����Ȃ��ړ�
void Weapon_WaterGun::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;

	// ������
	if ( isLeft )
	{
		moveX -= speedX;
	}
	// �E����
	else
	{
		moveX += speedX;
	}

	moveY += speedY;

	// �򋗗��͖���
	flightDistance -= 0.0f;

	BulletMove(false);
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
}

// �X�V����
void Weapon_WaterGun::Update()
{
	Move();
	Erase();
}

// �`�揈��
void Weapon_WaterGun::Draw(int scrollX, int scrollY,
						   int displaceX, int displaceY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX + displaceX,
					  (int)y - scrollY + displaceY,
					  0.75, 0.0, Graphic::GetInstance()->GetWaterGun(), true, isLeft);
	}
}