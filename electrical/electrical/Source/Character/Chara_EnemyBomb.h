#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// �ړ�
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);
};