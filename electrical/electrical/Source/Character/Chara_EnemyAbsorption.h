#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyAbsorption:public CharaEnemyBase
{
private:
	// �ړ�
	void Move();

public:
	Chara_EnemyAbsorption(float x, float y, int radius,
						  float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyAbsorption();

	// ����������
	void Initialize() override;

	// �X�V����
	void Update(float *shakeAddX, float *shakeAddY) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY) override;
};