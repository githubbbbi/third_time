#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);

	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update() = 0;

	// �`�揈��
	virtual void Draw() = 0;
};