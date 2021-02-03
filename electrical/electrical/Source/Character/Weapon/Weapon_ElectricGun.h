#pragma once

#include "WeaponBase.h"

extern const float EG_SPEED;

class Weapon_ElectricGun:public WeaponBase
{
private:
	double exRate;	// �g�嗦

	// �ړ�
	void Move();

	// ����
	void Erase();

public:
	Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
					   float flightDistance, int eraseFrame, bool isCharaLeftWard);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY, 
			  int displaceX, int displaceY);
};