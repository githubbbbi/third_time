#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	

public:
	CharaEnemyBase(int x, int y, int radius,
				   int speed, int hp, int graphHandle);
};