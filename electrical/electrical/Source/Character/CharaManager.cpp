#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyBombGH = LoadGraph("Resource/Graphic/Character/enemy_bomb.png");
	enemyGunGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	float startX = WIN_WIDTH / 2.0f;
	float startY = WIN_HEIGHT / 2.0f;

	// �v���C���[����
	player = new Chara_Player(startX, startY, 32, 
							  PLAYER_WIDTH, PLAYER_HEIGHT,
							  NORMAL_SPEED, 100, 1, playerGH);
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	{
		delete enemyBomb[i];
		enemyBomb.erase(enemyBomb.begin() + i);
	}

	for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	{
		delete enemyGun[i];
		enemyGun.erase(enemyGun.begin() + i);
	}
}

// ����������
void Chara_Manager::Initialize()
{

}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// �e�X�g�p
	{
		// ���e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_B) && enemyBomb.size() < 1 )
		{
			enemyBomb.push_back(new Chara_EnemyBomb(32.0f, 32.0f, 32,
													ENEMY_BOMB_WIDTH, ENEMY_BOMB_HEIGHT,
													NORMAL_SPEED, 2, 10, enemyBombGH));
		}

		// �e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_A) && enemyGun.size() < 1 )
		{
			enemyGun.push_back(new Chara_EnemyGun(32.0f, 32.0f, 32,
												  ENEMY_GUN_WIDTH, ENEMY_GUN_HEIGHT,
												  GetRand(3) + 2.0f, 2, 2, enemyGunGH));
		}
	}

	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive(),
							 &*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	{
		// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			delete enemyBomb[i];
			enemyBomb.erase(enemyBomb.begin() + i);
		}
	}

	// �e�G�l�~�[
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive(),
							&*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	{
		// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
		if ( !enemyGun[i]->GetIsAlive() )
		{
			delete enemyGun[i];
			enemyGun.erase(enemyGun.begin() + i);
		}
	}
}

// �L�����N�^���m�̓����蔻��
void Chara_Manager::CharaCollision()
{
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		// �G�ƃv���C���[�̔���
		// �G�Ɠ�����A�G���_�b�V����Ԃ�������A�v���C���[�Ƀ_���[�W������G��������
		if ( enemyBomb[i]->GetIsAlive() && player->GetIsAlive()
			&& Utility::IsCircleCollision(
				enemyBomb[i]->GetPosX(),
				enemyBomb[i]->GetPosY(),
				enemyBomb[i]->GetRadius() - 8,
				player->GetPosX(),
				player->GetPosY(),
				player->GetRadius() - 8
			) )
			if ( enemyBomb[i]->GetSpeed() == DASH_SPEED )
			{
				enemyBomb[i]->ReceiveDamage(player->GetAttackPower() * 2);
				player->ReceiveDamage(enemyBomb[i]->GetAttackPower());
			}

		//// �G�ƓG�̓����蔻��
		//for ( unsigned int j = 0; j < enemys.size(); j++ )
		//{
		//	// �����Ǝ����Ŕ��肵�Ȃ��悤��
		//	if ( j != i )
		//	{
		//		if ( enemys[i]->GetIsAlive() && enemys[j]->GetIsAlive()
		//			&& Utility::IsCircleCollision(
		//				enemys[i]->GetPosX(),
		//				enemys[i]->GetPosY(),
		//				enemys[i]->GetRadius() - 8,
		//				enemys[j]->GetPosX(),
		//				enemys[j]->GetPosY(),
		//				enemys[j]->GetRadius() - 8) )
		//		{
		//			enemys[j]->EnemiesCollision();
		//			enemys[j]->CharaJump();
		//		}
		//	}
		//}
	}
}

// �U�������Ǘ�
void Chara_Manager::WeaponManager()
{
	// �v���C���[�U��
	player->WeaponManager(electricGunGH);

	// �e�G�l�~�[�U��
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->WeaponManager(electricGunGH);
	}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( !enemyBomb[i]->GetIsAlive() || !player->GetIsAlive() )
		{
			break;
		}

		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( enemyBomb[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
										   enemyBomb[i]->GetPosY(),
										   enemyBomb[i]->GetRadius() - 8,
										   player->GetGunPosX(j),
										   player->GetGunPosY(j),
										   player->GetGunRadius(j) - 4) )
			{
				enemyBomb[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
			}
		}
	}

	// �e�G�l�~�[
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		if ( !enemyGun[i]->GetIsAlive() || !player->GetIsAlive() )
		{
			break;
		}

		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyGun[i]->GetPosX(),
											enemyGun[i]->GetPosY(),
											enemyGun[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemyGun[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
			}
		}

		// �G�l�~�[�̍U���ƃv���C���[�̓����蔻��
		for ( unsigned int j = 0; j < enemyGun[i]->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyGun[i]->GetGunPosX(j),
											enemyGun[i]->GetGunPosY(j),
											enemyGun[i]->GetGunRadius(j) - 8,
											player->GetPosX(),
											player->GetPosY(),
											player->GetRadius() - 4) )
			{
				enemyGun[i]->HitAttack(j);
				player->ReceiveDamage(enemyGun[i]->GetAttackPower());
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
void Chara_Manager::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// �v���C���[
	player->Draw(shakeX, shakeY, scrollX, scrollY);

	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// �e�G�l�~�[
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// �f�o�b�O�p
	DrawFormatString(50, 100, GetColor(255, 255, 255), "B�L�[�ŃG�l�~�[���� ���e�G�l�~�[�̐�:%d", enemyBomb.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "A�L�[�ŃG�l�~�[���� �e�G�l�~�[�̐�:%d", enemyGun.size());
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