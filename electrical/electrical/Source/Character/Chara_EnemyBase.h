#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	bool blockFlag;		//�u���b�N�����邩�Ȃ����̃t���O
	float enemySpace;	//�v���C���[�ƓG�̃u���b�N��

	// �V�F�C�N�X�^�[�g
	void ShakeStart(float *shakeAddX, float *shakeAddY);

public:
	Chara_EnemyBase(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);

	//�G�̓����蔻��
	void EnemiesCollision();

	// �u���b�N���Ԃɂ��邩�T��
	void FindBlock(float playerX);
};