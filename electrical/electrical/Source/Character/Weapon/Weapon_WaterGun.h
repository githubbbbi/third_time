#pragma once

#include "WeaponBase.h"

extern const float WG_GRAVITY;

class Weapon_WaterGun:public WeaponBase
{
private:
	// ˆÚ“®
	void Move();

	// Á‹
	void Erase();

public:
	Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
					int eraseFrame, bool isCharaLeftWard);

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw(int scrollX, int scrollY);
};