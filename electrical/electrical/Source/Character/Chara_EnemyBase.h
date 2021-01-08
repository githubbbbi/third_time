#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	// �W�����v����
	void Jump();

	// �i�s������ς���
	void ChangeDirection();

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// �V�F�C�N�X�^�[�g
	void ShakeStart(float *shakeAddX, float *shakeAddY);

	// �v���C���[�Ƃ̊ԂɃu���b�N�����邩�T��
	bool IsBlock(float playerX);

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int graphHandle);

	// �G�̓����蔻��
	void EnemiesCollision();
};