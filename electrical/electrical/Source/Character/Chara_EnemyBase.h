#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int graphHandle);
};