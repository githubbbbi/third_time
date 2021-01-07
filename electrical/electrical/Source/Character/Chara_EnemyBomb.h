#pragma once

#include "Chara_EnemyBase.h"

const int ENEMY_BOMB_WIDTH = 30;	// ‰¡•
const int ENEMY_BOMB_HEIGHT = 30;	// c•

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// ˆÚ“®
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
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