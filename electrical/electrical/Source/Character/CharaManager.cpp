#include "../Utility/Utility.h"
#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	// �v���C���[����
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
		32, NORMAL_SPEED, 100, 1, playerGH);
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

}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// �z��
	// �e�X�g�p
	{
		static int frame = 0;
		frame++;
		if ( frame % 300 == 0 )
		{
			{
				// �z���G�l�~�[
				enemys.push_back(new Chara_EnemyAbsorption(32.0f, 32.0f, 32,
					GetRand(3) + 2.0f, 2, 20, enemyAbsorptionGH));
			}
		}
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(&*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
		if ( !enemys[i]->GetIsAlive() )
		{
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// �L�����N�^���m�̓����蔻��
void Chara_Manager::CharaCollision()
{
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// �����ɋL�q
		//�G�ƃv���C���[�̔���
		//���������������Ă��ăv���C���[���G�̌���ǂ�������ꍇ�A�G�͐i��
		if ( enemys[i]->GetIsAlive() && player->GetIsAlive()
			&& Utility::IsCircleCollision(
				enemys[i]->GetPosX(),
				enemys[i]->GetPosY(),
				enemys[i]->GetRadius() - 8,
				player->GetPosX(),
				player->GetPosY(),
				player->GetRadius() - 8
			) )
			if ( !enemys[i]->GetIsLeftWard() && !player->GetIsLeftWard()
				&& enemys[i]->GetPosX() > player->GetPosX()
				|| enemys[i]->GetIsLeftWard() && player->GetIsLeftWard()
				&& enemys[i]->GetPosX() < player->GetPosX() )
			{
				player->CharaCollision();
				player->CharaJump();
			}
			else
			{
				player->CharaJump();
				player->CharaCollision();
				enemys[i]->CharaCollision();
			}

		//�G�ƓG�̓����蔻��
		for ( unsigned int j = 0; j < enemys.size(); j++ )
		{
			//�����Ǝ����Ŕ��肵�Ȃ��悤��
			if ( j != i )
			{
				if ( enemys[i]->GetIsAlive() && enemys[j]->GetIsAlive()
					&& Utility::IsCircleCollision(
						enemys[i]->GetPosX(),
						enemys[i]->GetPosY(),
						enemys[i]->GetRadius() - 8,
						enemys[j]->GetPosX(),
						enemys[j]->GetPosY(),
						enemys[j]->GetRadius() - 8) )
				{
					enemys[j]->EnemiesCollision();
					enemys[j]->CharaJump();
				}
			}
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
			16, 30.0f,
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
			if ( enemys[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemys[i]->GetPosX(),
					enemys[i]->GetPosY(),
					enemys[i]->GetRadius() - 8,
					electricGun[j]->GetPosX(),
					electricGun[j]->GetPosY(),
					electricGun[j]->GetRadius() - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower());
				electricGun[j]->Hit();
			}
		}
	}
}

// �X�V����
void Chara_Manager::Update(float *shakeAddX, float *shakeAddY)
{
	// �v���C���[
	player->Update();

	//�L�����̓����蔻��
	CharaCollision();

	// �U������
	WeaponManager();

	// �G�l�~�[
	EnemyManager(&*shakeAddX, &*shakeAddY);

	// �U���̓����蔻��
	AttackCollision();
}

// �`�揈��
void Chara_Manager::Draw(float shakeX, float shakeY)
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