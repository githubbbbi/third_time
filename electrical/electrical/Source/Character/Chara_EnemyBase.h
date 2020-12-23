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

	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(float playerX, float playerY,
						float *shakeAddX, float *shakeAddY) = 0;

	// �`�揈��
	virtual void Draw(float shakeX, float shakeY) = 0;

	//�G�̓����蔻��
	void EnemiesCollision();

	// �U�������Ǘ�
	virtual void WeaponManager(int electricGunGH) = 0;
};