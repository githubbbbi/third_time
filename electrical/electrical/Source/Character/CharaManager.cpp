#include "../Utility/Utility.h"
#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	player = nullptr;

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
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
							  32, NORMAL_SPEED, 100, 1, playerGH);

	// �V�F�C�N������
	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager()
{
	// �z��
	// �e�X�g
	{
		// B�L�[�A�p�b�h��B�{�^���ŃG�l�~�[����
		if ( InputKey::IsKeyInputNow(KEY_INPUT_B) ||
			InputPad::IsPadInputNow(PAD_INPUT_B) )
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
			// �V�F�C�N �e�X�g
			{
				shakeAddX = shakeAddY = 6.0f;
			}

			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// �U�������̊Ǘ�
void Chara_Manager::WeaponManager()
{
	// ����
	if ( player->IsAttack() && player->GetIsAlive() )
	{
		electricGun.push_back(new ElectricGun(player->GetPosX(),
											  player->GetPosY(),
											  16, 25,
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
											enemys[i]->GetRadius() - 8,
											electricGun[j]->GetPosX(),
											electricGun[j]->GetPosY(),
											electricGun[j]->GetRadius() - 4) )
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

	// �V�F�C�N
	Utility::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddX);
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
	player->Draw(shakeX, shakeY);

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 20, GetColor(255, 255, 255), "B�{�^���ŃG�l�~�[���� �G�l�~�[�̐�:%d", enemys.size());
	DrawFormatString(0, 40, GetColor(255, 255, 255), "SPACE�L�[�܂���X�{�^���ōU��");
}