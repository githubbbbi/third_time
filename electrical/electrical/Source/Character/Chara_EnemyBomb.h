#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// �ړ�
	void Move(float playerX, float playerY);

public:
	Chara_EnemyBomb(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ����������
	void Initialize() override;

	// �X�V����
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY) override;

	// �U�������Ǘ�
	void WeaponManager(int electricGunGH) override;
};