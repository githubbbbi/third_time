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

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
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
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, 5.0f, 50, playerGH);

	// �G�l�~�[����
	enemyAbsorption[enemyAbsorptionNum] =
	{
		new Chara_EnemyAbsorption(32.0f, WIN_HEIGHT / 2.0f,
								   32, 5.0f, 2, enemyAbsorptionGH)
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
		if ( InputPad::IsPadInputNow(PAD_INPUT_B) &&
			enemyAbsorptionNum < ENEMY_MAX_NUM )
		{
			enemyAbsorption[enemyAbsorptionNum] =
			{
				new Chara_EnemyAbsorption(32.0f, 32.0f,
										  32, GetRand(3) + 2.0f, 2,enemyAbsorptionGH)
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

	// �f�o�b�O�p
	DrawFormatString(0, 20, GetColor(255, 255, 255), "X�L�[��������B�{�^���œG���o:%d�̕��o", enemyAbsorptionNum);
}