#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyAbsorption:public CharaEnemyBase
{
private:
	// ˆÚ“®
	void Move();

public:
	Chara_EnemyAbsorption(float x, float y, int radius,
						  float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyAbsorption();

	// ‰Šú‰»ˆ—
	void Initialize() override;

	// XVˆ—
	void Update() override;

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY) override;
};