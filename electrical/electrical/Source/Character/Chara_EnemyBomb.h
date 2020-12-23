#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// ˆÚ“®
	void Move(float playerX, float playerY);

public:
	Chara_EnemyBomb(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ‰Šú‰»ˆ—
	void Initialize() override;

	// XVˆ—
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY) override;

	// UŒ‚ˆ—ŠÇ—
	void WeaponManager(int electricGunGH) override;
};