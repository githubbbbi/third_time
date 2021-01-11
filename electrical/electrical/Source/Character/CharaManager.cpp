#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyBombGH = LoadGraph("Resource/Graphic/Character/enemy_bomb.png");
	enemyGunGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	enemyWaterGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");
	waterBulletGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");


	explosionX = 0.0f;
	explosionY = 0.0f;

	float startX = WIN_WIDTH / 2.0f;
	float startY = 0.0f;

	// �v���C���[����
	player = new Chara_Player(startX, startY, 32,
							  P_WIDTH, P_HEIGHT,
							  P_NORMAL_SPEED, 100, 1, playerGH);
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
void Chara_Manager::EnemyManager()
{
	// �e�X�g�p
	{
		static int timer = 0;
		timer++;
		// ���e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_B) && timer % 30 == 0 )
		{
			enemyBomb.push_back(new Chara_EnemyBomb(WIN_WIDTH / 2.0f, 0.0f, 32,
													E_BOMB_WIDTH, E_BOMB_HEIGHT,
													E_BOMB_NORMAL_SPEED, 2, 10, enemyBombGH));
		}

		// �e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_A) && timer % 30 == 0 )
		{
			enemyGun.push_back(new Chara_EnemyGun(WIN_WIDTH / 2.0f, 0.0f, 32,
												  E_GUN_WIDTH, E_GUN_HEIGHT,
												  E_GUN_NORMAL_SPEED, 2, 2, enemyGunGH));
		}

		// ���e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_C) && timer % 30 == 0 )
		{
			enemyWater.push_back(new Chara_EnemyWater(WIN_WIDTH / 2.0f, 0.0f, 32,
				E_WATER_WIDTH, E_WATER_HEIGHT,
				0.0f, 2, 2, enemyWaterGH));
		}
	}

	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	//for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	//{
	//	// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
	//	if ( !enemyBomb[i]->GetIsAlive() )
	//	{
	//		delete enemyBomb[i];
	//		enemyBomb.erase(enemyBomb.begin() + i);
	//	}
	//}

	// �e�G�l�~�[
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	//for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	//{
	//	// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
	//	if ( !enemyGun[i]->GetIsAlive() )
	//	{
	//		delete enemyGun[i];
	//		enemyGun.erase(enemyGun.begin() + i);
	//	}
	//}

	// ���e�G�l�~�[
	for (unsigned int i = 0; i < enemyWater.size(); i++)
	{
		enemyWater[i]->Update(player->GetPosX(), player->GetPosY());
	}

	//for ( int i = enemyWater.size() - 1; i >= 0; i-- )
	//{
	//	// ���S���ʊO�ɏo���ꍇ�A�G�l�~�[�폜
	//	if ( !enemyWater[i]->GetIsAlive() )
	//	{
	//		delete enemyWater[i];
	//		enemyWater.erase(enemyWater.begin() + i);
	//	}
	//}
}

// �L�����N�^���m�̓����蔻��
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		// �v���C���[�ƓG�Ƃ̔���
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		/*if ( Utility::IsRectCollision(enemyBomb[i]->GetPosX(),
									  enemyBomb[i]->GetPosY(),
									  enemyBomb[i]->GetWidth(),
									  enemyBomb[i]->GetHeight(),
									  player->GetPosX(),
									  player->GetPosY(),
									  player->GetWidth(),
									  player->GetHeight()) )
		{
			player->CharactersCollision();
		}*/
	}
}

// ���폈���Ǘ�
void Chara_Manager::WeaponManager()
{
	// �v���C���[�U��
	player->WeaponManager(electricGunGH);

	// �e�G�l�~�[�U��
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->WeaponManager(electricGunGH);
	}

	// ���e�G�l�~�[�U��
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		enemyWater[i]->WeaponManager(player->GetPosX(), player->GetPosY(),
									player->GetIsAlive(), waterBulletGH);
	}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		// ���e�G�l�~�[���_�b�V����Ԃ�������A�v���C���[�Ƀ_���[�W������G��������
		if ( Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
										enemyBomb[i]->GetPosY(),
										enemyBomb[i]->GetRadius() - 8,
										player->GetPosX(),
										player->GetPosY(),
										player->GetRadius() - 8) )
		{
			if ( fabsf(enemyBomb[i]->GetSpeed()) == E_BOMB_DASH_SPEED )
			{
				enemyBomb[i]->HitAttack();
				player->ReceiveDamage(enemyBomb[i]->GetAttackPower());
			}
		}

		// �v���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
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
		if ( !enemyGun[i]->GetIsAlive() )
		{
			continue;
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

	// ���e�G�l�~�[
	for (unsigned int i = 0; i < enemyWater.size(); i++)
	{
		if (!enemyWater[i]->GetIsAlive())
		{
			continue;
		}

		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		for (unsigned int j = 0; j < player->GetGunSize(); j++)
		{
			if (Utility::IsCircleCollision(enemyWater[i]->GetPosX(),
				enemyWater[i]->GetPosY(),
				enemyWater[i]->GetRadius() - 8,
				player->GetGunPosX(j),
				player->GetGunPosY(j),
				player->GetGunRadius(j) - 4))
			{
				enemyWater[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
			}
		}

		// �G�l�~�[�̍U���ƃv���C���[�̓����蔻��
		for (unsigned int j = 0; j < enemyWater[i]->GetGunSize(); j++)
		{
			if (Utility::IsCircleCollision(enemyWater[i]->GetGunPosX(j),
				enemyWater[i]->GetGunPosY(j),
				enemyWater[i]->GetGunRadius(j) - 8,
				player->GetPosX(),
				player->GetPosY(),
				player->GetRadius() - 4))
			{
				enemyWater[i]->HitAttack(j);
				player->ReceiveDamage(enemyWater[i]->GetAttackPower());
			}
		}
	}
}

// �X�V����
void Chara_Manager::Update()
{
	// �v���C���[
	player->Update();

	//�L�����̓����蔻��
	CharaCollision();

	// ���폈��
	WeaponManager();

	// �G�l�~�[
	EnemyManager();

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

	// ���e�G�l�~�[
	for (unsigned int i = 0; i < enemyWater.size(); i++)
	{
		enemyWater[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// �f�o�b�O�p
	DrawFormatString(50, 100, GetColor(255, 255, 255), "B�L�[�ŃG�l�~�[���� ���e�G�l�~�[�̐�:%d", enemyBomb.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "A�L�[�ŃG�l�~�[���� �e�G�l�~�[�̐�:%d", enemyGun.size());
	DrawFormatString(50, 140, GetColor(255, 255, 255), "C�L�[�ŃG�l�~�[���� ���e�G�l�~�[�̐�:%d", enemyWater.size());
	DrawFormatString(300, 200, GetColor(255, 255, 255), "�v���C���[��Y���W%f", player->GetPosY());
	if ( enemyBomb.size() >= 1 )
	{
		DrawFormatString(300, 220, GetColor(255, 255, 255), "�G��X���W%f", enemyBomb[0]->GetPosX());
		DrawFormatString(300, 240, GetColor(255, 255, 255), "�G��Y���W%f", enemyBomb[0]->GetPosY());
	}
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

// �G�l�~�[�̎��S
bool Chara_Manager::GetIsEnemyDeath()
{
	// ���e�G�l�~�[
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemyBomb[i]->GetIsAlive() )
		{
			// ���W���擾
			explosionX = enemyBomb[i]->GetPosX();
			explosionY = enemyBomb[i]->GetPosY();

			// �G�l�~�[������
			delete enemyBomb[i];
			enemyBomb.erase(enemyBomb.begin() + i);

			return true;
		}
	}

	// �e�G�l�~�[
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		if ( enemyGun[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemyGun[i]->GetIsAlive() )
		{
			// ���W���擾
			explosionX = enemyGun[i]->GetPosX();
			explosionY = enemyGun[i]->GetPosY();

			// �G�l�~�[������
			delete enemyGun[i];
			enemyGun.erase(enemyGun.begin() + i);

			return true;
		}
	}

	// ���e�G�l�~�[
	for (unsigned int i = 0; i < enemyWater.size(); i++)
	{
		if (enemyWater[i]->GetIsAlive())
		{
			continue;
		}

		if (!enemyWater[i]->GetIsAlive())
		{
			// ���W���擾
			explosionX = enemyWater[i]->GetPosX();
			explosionY = enemyWater[i]->GetPosY();

			// �G�l�~�[������
			delete enemyWater[i];
			enemyWater.erase(enemyWater.begin() + i);

			return true;
		}
	}

	return false;
}