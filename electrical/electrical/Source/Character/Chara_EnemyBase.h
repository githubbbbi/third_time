#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	// �V�F�C�N�X�^�[�g
	void ShakeStart(float *shakeAddX, float *shakeAddY);

public:
	Chara_EnemyBase(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);

	//�G�̓����蔻��
	void EnemiesCollision();
};