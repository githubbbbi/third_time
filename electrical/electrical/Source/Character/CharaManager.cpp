#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	player = nullptr;

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// ����������
void Chara_Manager::Initialize()
{
	// �v���C���[����
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, 5.0f, 50, 1, playerGH);
}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager()
{
	// �z��
	// �e�X�g
	{
		// �p�b�h��A�{�^���ŃG�l�~�[����
		if ( InputPad::IsPadInputNow(PAD_INPUT_B) )
		{
			// �z���G�l�~�[
			enemys.push_back(new Chara_EnemyAbsorption(32.0f, 32.0f, 32,
													   GetRand(3) + 2.0f, 2, 20, enemyAbsorptionGH));
		}
	}

	for ( int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update();
	}

	// �G�l�~�[�폜
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	for ( int i = 0; i < enemys.size(); i++ )
	{
		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		// ��������


		// �����܂�

		// �v���C���[�̍U���ƃq�b�g�������A���̊֐����Ă΂��@�܂�܎g���đ��v�Ȃ͂�
		// enemys[i]->ReceiveDamage(player->GetAttackPower());
	}
}

// �X�V����
void Chara_Manager::Update()
{
	// �v���C���[
	player->Update();

	// �G�l�~�[
	EnemyManager();

	// �U���̓����蔻��
	AttackCollision();
}

// �`�揈��
void Chara_Manager::Draw()
{
	// �v���C���[
	player->Draw();

	// �G�l�~�[
	for ( int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw();
	}

	// �f�o�b�O�p
	DrawFormatString(0, 20, GetColor(255, 255, 255), "X�L�[�܂���B�{�^���ŃG�l�~�[���� �G�l�~�[�̐�:%d", enemys.size());
	DrawFormatString(0, 40, GetColor(255, 255, 255), "SPACE�L�[�܂���X�{�^���ōU��(�}�C�i�X�����ɂ��������܂���)");
}