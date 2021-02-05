#pragma once

#include "WeaponBase.h"

extern const float WG_GRAVITY;

class Weapon_WaterGun:public WeaponBase
{
private:
	// �ړ�
	void Move();

	// ����
	void Erase();

public:
	Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
					float flightDistance, int eraseFrame, bool isCharaLeft);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY, 
			  int displaceX, int displaceY);
};