#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	// ˆÚ“®
	void Move(float playerX, float playerY);

public:
	Chara_EnemyGun(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ‰Šú‰»ˆ—
	void Initialize() override;

	// XVˆ—
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY) override;

	// UŒ‚ˆ—ŠÇ—
	void WeaponManager(int electricGunGH) override;

	// UŒ‚ƒqƒbƒg
	void HitAttack(int index);

	// “d‹Ce‚Ì—v‘f”
	unsigned int GetGunSize();

	// “d‹Ce‚ÌXÀ•Wæ“¾
	float GetGunPosX(int index);

	// “d‹Ce‚ÌYÀ•Wæ“¾
	float GetGunPosY(int index);

	// “d‹Ce‚Ìradiusæ“¾
	int GetGunRadius(int index);
};