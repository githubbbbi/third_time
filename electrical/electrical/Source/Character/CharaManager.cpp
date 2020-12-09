#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

#define ENEMY_MAX_NUM 1000

Chara_Manager::Chara_Manager()
{
	player = nullptr;
	enemyAbsorption = new Chara_EnemyAbsorption * [ENEMY_MAX_NUM];

	enemyAbsorptionNum = 0;

	playerGH = LoadGraph("Resource/Graphic/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/enemy_absorption.png");
}

Chara_Manager::~Chara_Manager()
{
	delete player;
	delete[] enemyAbsorption;
}

// ����������
void Chara_Manager::Initialize()
{
	// �v���C���[����
	player = new Chara_Player(WIN_WIDTH / 2, WIN_HEIGHT / 2, 5,
							  32, playerGH);

	// �G�l�~�[����
	enemyAbsorption[enemyAbsorptionNum] =
	{
		new Chara_EnemyAbsorption(32, WIN_HEIGHT / 2, 5,
								  32, enemyAbsorptionGH)
	};

	enemyAbsorptionNum = 1;
}

// �X�V����
void Chara_Manager::Update()
{
	// �v���C���[
	player->Update();

	// �G�l�~�[
	// �z��
	// �e�X�g
	{
		// �p�b�h��A�{�^���ŃG�l�~�[����
		if ( InputPad::IsPadInputTrigger(PAD_INPUT_A) &&
			enemyAbsorptionNum < ENEMY_MAX_NUM )
		{
			enemyAbsorption[enemyAbsorptionNum] =
			{
				new Chara_EnemyAbsorption(32, GetRand(WIN_HEIGHT - 64) + 32, GetRand(3) + 2,
										  32, enemyAbsorptionGH)
			};

			enemyAbsorptionNum++;
		}
	}

	for ( int i = 0; i < enemyAbsorptionNum; i++ )
	{
		enemyAbsorption[i]->Update();
	}
}

// �`�揈��
void Chara_Manager::Draw()
{
	// �v���C���[
	player->Draw();

	// �G�l�~�[
	// �z��
	for ( int i = 0; i < enemyAbsorptionNum; i++ )
	{
		enemyAbsorption[i]->Draw();
	}
}