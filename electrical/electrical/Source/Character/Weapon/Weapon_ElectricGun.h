#pragma once

#include "WeaponBase.h"

extern const float EG_SPEED;

class Weapon_ElectricGun:public WeaponBase
{
private:
	double exRate;	// Šg‘å—¦

	// ˆÚ“®
	void Move();

	// Á‹
	void Erase();

public:
	Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
					   float flightDistance, int eraseFrame, bool isCharaLeft);

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw(int scrollX, int scrollY, 
			  int displaceX, int displaceY);
};