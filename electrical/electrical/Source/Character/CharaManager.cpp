#include "../Utility/Utility.h"
#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	player = nullptr;

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}

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

	for ( unsigned int i = 0; i < enemys.size(); i++ )
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

// �U�������̊Ǘ�
void Chara_Manager::WeaponManager()
{
	// ����
	if ( player->IsAttack() )
	{
		electricGun.push_back(new ElectricGun(player->GetPosX(),
											  player->GetPosY(),
											  16, 15, 
											  player->GetIsLeftWard(),
											  electricGunGH));
	}

	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Update();
	}

	// �d�C�e�폜
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		if ( !electricGun[i]->GetIsAlive() )
		{
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}
	}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < electricGun.size(); j++ )
		{
			if ( Utility::IsCircleCollision(enemys[i]->GetPosX(),
											enemys[i]->GetPosY(),
											enemys[i]->GetRadius(),
											electricGun[j]->GetPosX(),
											electricGun[j]->GetPosY(),
											electricGun[j]->GetRadius()) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower());
				electricGun[j]->BulletHit();
			}
		}
	}
}

// �X�V����
void Chara_Manager::Update()
{
	// �v���C���[
	player->Update();

	// �U������
	WeaponManager();

	// �G�l�~�[
	EnemyManager();

	// �U���̓����蔻��
	AttackCollision();
}

// �`�揈��
void Chara_Manager::Draw()
{
	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw();
	}

	// �v���C���[
	player->Draw();

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw();
	}

	// �f�o�b�O�p
	DrawFormatString(0, 20, GetColor(255, 255, 255), "X�L�[�܂���B�{�^���ŃG�l�~�[���� �G�l�~�[�̐�:%d", enemys.size());
	DrawFormatString(0, 40, GetColor(255, 255, 255), "SPACE�L�[�܂���X�{�^���ōU��");
}