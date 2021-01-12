#pragma once

#include "WeaponBase.h"

const float WG_GRAVITY = 0.85f;

class Weapon_WaterGun:public WeaponBase
{
private:
	// ˆÚ“®
	void Move();

	// Á‹
	void Erase();

public:
	Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
					int eraseFrame, bool isCharaLeftWard, int graphHandle);

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw(int scrollX, int scrollY);
};