#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyAbsorption:public CharaEnemyBase
{
private:
	// ˆÚ“®
	void Move();

public:
	Chara_EnemyAbsorption(int x, int y, int radius,
						  int speed, int hp, int graphHandle);
	~Chara_EnemyAbsorption();

	// ‰Šú‰»ˆ—
	void Initialize();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw();
};