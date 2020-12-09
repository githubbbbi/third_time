#pragma once

#include "CharaBase.h"

class Chara_Player:public CharaBase
{
private:
	// ˆÚ“®
	void Move();

public:
	Chara_Player(int x, int y, int speed,
					int radius, int graphHandle);
	~Chara_Player();

	// ‰Šú‰»ˆ—
	void Initialize();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw();
};