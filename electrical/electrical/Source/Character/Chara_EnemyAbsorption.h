#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyAbsorption:public CharaEnemyBase
{
private:
	// �ړ�
	void Move();

public:
	Chara_EnemyAbsorption(int x, int y, int radius,
						  int speed, int hp, int graphHandle);
	~Chara_EnemyAbsorption();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};