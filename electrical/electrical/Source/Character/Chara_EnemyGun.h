#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

const int BULLET_INTERVAL = 70;

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// Œ‚‚Á‚½’e”
	int bulletInterval;		// e‚ğŒ‚‚ÂŠÔŠu
	bool isTargetLock;		// ”ÍˆÍ“à‚Ìƒtƒ‰ƒO


	// ˆÚ“®
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyGun(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ‰Šú‰»ˆ—
	void Initialize();

	// XVˆ—
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// UŒ‚ˆ—ŠÇ—
	void WeaponManager(int electricGunGH);

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