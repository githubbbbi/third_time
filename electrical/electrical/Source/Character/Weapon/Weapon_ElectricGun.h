#pragma once

#include "WeaponBase.h"

const float EG_SPEED = 10.0f;
const int EG_ALIVE_TIME = 30;

class Weapon_ElectricGun:public WeaponBase
{
private:
	double exRate;	// �g�嗦
	int aliveTimer;	// �����^�C�}�[

	// �ړ�
	void Move();

	// ����
	void Erase();

public:
	Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
					   int eraseFrame, bool isCharaLeftWard, int graphHandle);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);
};