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
					int eraseFrame, bool isCharaLeftWard, int graphHandle);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);
};