#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	// �V�F�C�N�X�^�[�g
	void ShakeStart(float *shakeAddX, float *shakeAddY);

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);

	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(float *shakeAddX, float *shakeAddY) = 0;

	// �`�揈��
	virtual void Draw(float shakeX, float shakeY) = 0;
};