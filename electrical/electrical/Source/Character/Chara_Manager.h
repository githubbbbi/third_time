#pragma once

#include <vector>

#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyAbsorption.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<CharaEnemyBase *>enemys;

	int playerGH;
	int enemyAbsorptionGH;

	// �G�l�~�[�Ǘ�
	void EnemyManager();

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