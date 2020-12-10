#pragma once

#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyAbsorption.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	Chara_EnemyAbsorption **enemyAbsorption;

	int playerGH;
	int enemyAbsorptionGH;

	int enemyAbsorptionNum;	// �z���G�l�~�[�̐�

public:
	Chara_Manager();
	~Chara_Manager();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};