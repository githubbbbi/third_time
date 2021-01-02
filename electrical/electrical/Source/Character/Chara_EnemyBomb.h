#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// ˆÚ“®
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ‰Šú‰»ˆ—
	void Initialize();

	// XVˆ—
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);
};