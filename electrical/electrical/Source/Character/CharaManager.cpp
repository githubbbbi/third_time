#include "DxLib.h"
#include "Chara_Manager.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"

Chara_Manager::Chara_Manager()
{
	explosionX = 0.0f;
	explosionY = 0.0f;

	float startX = 0.0f + CHIP_SIZE * 2.0f;
	float startY = 0.0f;

	// �v���C���[����
	player = new Chara_Player(startX, startY, 32,
							  P_WIDTH, P_HEIGHT,
							  P_NORMAL_SPEED, 100, 1);
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
	player->Initialize();

	// �G�l�~�[�͑S�ď��������Ⴄ
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// �G�l�~�[�̐���
void Chara_Manager::EnemySpawn(int screenX, int screenY)
{
	// �e�X�g�p
	float startX = 0.0f + CHIP_SIZE * 2.0f;
	float startY = 0.0f;
	static int timer = 0;
	timer++;

	// ���e�G�l�~�[
	if ( CheckHitKey(KEY_INPUT_B) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyBomb(startX, startY, 32,
											 EB_WIDTH, EB_HEIGHT,
											 EB_NORMAL_SPEED, 2, 10));
	}

	// �e�G�l�~�[
	if ( CheckHitKey(KEY_INPUT_A) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyElectric(startX, startY, 32,
												 EE_WIDTH, EE_HEIGHT,
												 EE_NORMAL_SPEED, 2, 2));
	}

	// ���e�G�l�~�[
	if ( CheckHitKey(KEY_INPUT_C) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyWater(startX, startY, 32,
											  EW_WIDTH, EW_HEIGHT,
											  0.0f, 2, 2));
	}
}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager(int screenX, int screenY)
{
	// �G�l�~�[�̏o��
	EnemySpawn(screenX, screenY);

	// �X�V����
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	// �X�N���[���O�ɏo���ꍇ����
	/*for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}*/
}

// �L�����N�^���m�̓����蔻��
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	//for ( unsigned int i = 0; i < enemys.size(); i++ )
	//{
	//	// �v���C���[�ƓG�Ƃ̔���
	//	if ( !enemys[i]->GetIsAlive() )
	//	{
	//		continue;
	//	}

	//	if ( Utility::IsRectCollision(enemys[i]->GetPosX(),
	//								  enemys[i]->GetPosY(),
	//								  enemys[i]->GetWidth(),
	//								  enemys[i]->GetHeight(),
	//								  player->GetPosX(),
	//								  player->GetPosY(),
	//								  player->GetWidth(),
	//								  player->GetHeight()) )
	//	{
	//		player->CharactersCollision();
	//	}
	//}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			continue;
		}

		// �v���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemys[i]->GetPosX(),
											enemys[i]->GetPosY(),
											enemys[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower(),
										 player->GetIsGunLeftWard(j));
				player->HitAttack(j);
			}
		}

		if ( player->GetIsInvicible() )
		{
			return;
		}

		// �G�l�~�[�̍U���ƃv���C���[�̓����蔻��
		if ( Utility::IsCircleCollision(enemys[i]->GetAttackPosX(),
									   enemys[i]->GetAttackPosY(),
									   enemys[i]->GetAttackRadius() - 8,
									   player->GetPosX(),
									   player->GetPosY(),
									   player->GetRadius() - 4) )
		{
			enemys[i]->HitAttack();
			player->ReceiveDamage(enemys[i]->GetAttackPower(),
								  enemys[i]->GetIsAttackLeftWard());
		}
		/*for ( unsigned int j = 0; j < enemys[i]->GetGunSize(); j++ )
		{
			if ( !player->GetIsInvicible() &&
				Utility::IsCircleCollision(enemys[i]->GetGunPosX(j),
										   enemys[i]->GetGunPosY(j),
										   enemys[i]->GetGunRadius(j) - 8,
										   player->GetPosX(),
										   player->GetPosY(),
										   player->GetRadius() - 4) )
			{
				enemys[i]->HitAttack(j);
				player->ReceiveDamage(enemys[i]->GetAttackPower(),
									  enemys[i]->GetIsGunLeftWard(j));
			}
		}*/
	}
}

// �X�V����
void Chara_Manager::Update(int screenX, int screenY)
{
	// �v���C���[
	player->Update();

	//�L�����̓����蔻��
	CharaCollision();

	// �G�l�~�[
	EnemyManager(screenX, screenY);

	// �U���̓����蔻��
	AttackCollision();
}

// �`�揈��
void Chara_Manager::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// �v���C���[
	player->Draw(shakeX, shakeY, scrollX, scrollY);

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// �f�o�b�O�p
	DrawFormatString(50, 100, GetColor(255, 255, 255), "B�L�[�ŃG�l�~�[���� ���e�G�l�~�[�̐�:%d", enemys.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "A�L�[�ŃG�l�~�[���� �e�G�l�~�[�̐�:%d", enemys.size());
	DrawFormatString(50, 140, GetColor(255, 255, 255), "C�L�[�ŃG�l�~�[���� ���e�G�l�~�[�̐�:%d", enemys.size());
	/*DrawFormatString(300, 200, GetColor(255, 255, 255), "�v���C���[��Y���W%f", player->GetPosY());
	if ( enemyBomb.size() >= 1 )
	{
		DrawFormatString(300, 220, GetColor(255, 255, 255), "�G��X���W%f", enemyBomb[0]->GetPosX());
		DrawFormatString(300, 240, GetColor(255, 255, 255), "�G��Y���W%f", enemyBomb[0]->GetPosY());
	}*/
}

// �X�N���[���̒��SX���W���擾
float Chara_Manager::GetScrollCenterX()
{
	return player->GetPosOldX();
}

// �X�N���[���̒��SY���W���擾
float Chara_Manager::GetScrollCenterY()
{
	return player->GetPosOldY();
}

// �G�l�~�[�̎��SX���W���擾
float Chara_Manager::GetExplosionPosX()
{
	return explosionX;
}

// �G�l�~�[�̎��SY���W���擾
float Chara_Manager::GetExplosionPosY()
{
	return explosionY;
}

// �L�����N�^�[�̎��S
bool Chara_Manager::GetIsCharaDeath()
{
	// �v���C���[
	if ( !player->GetIsAlive() )
	{
		// ���W���擾
		explosionX = player->GetPosX();
		explosionY = player->GetPosY();

		return true;
	}

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemys[i]->GetIsAlive() )
		{
			// ���W���擾
			explosionX = enemys[i]->GetPosX();
			explosionY = enemys[i]->GetPosY();

			// �G�l�~�[������
			delete enemys[i];
			enemys.erase(enemys.begin() + i);

			return true;
		}
	}

	return false;
}

// �v���C���[��HP���擾
int Chara_Manager::GetPlayerHp()
{
	return player->GetHp();
}

// �v���C���[�̍ő�HP���擾
int Chara_Manager::GetPlayerMaxHp()
{
	return P_MAX_HP;
}

// �v���C���[�̍ő�o�b�e���[���擾
int Chara_Manager::GetPlayerBattery()
{
	return player->GetBattery();
}

// �v���C���[�̃o�b�e���[���擾
int Chara_Manager::GetPlayerMaxBattery()
{
	return P_MAX_BATTERY;
}