#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int graphHandle);

	// isAlive‚ğæ“¾
	bool GetIsAlive();

	// ‰Šú‰»ˆ—
	virtual void Initialize() = 0;

	// XVˆ—
	virtual void Update() = 0;

	// •`‰æˆ—
	virtual void Draw() = 0;
};