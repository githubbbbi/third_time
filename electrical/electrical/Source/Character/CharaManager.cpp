#include "../Utility/Utility.h"
#include "DxLib.h"
#include "../Define/Define.h"
#include "Chara_Manager.h"
#include "../Character/Chara_EnemyBomb.h"
#include "../Character/Chara_EnemyGun.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyBombGH = LoadGraph("Resource/Graphic/Character/enemy_bomb.png");
	enemyGunGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	// �v���C���[����
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, NORMAL_SPEED, 100, 1, playerGH);
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

}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// �e�X�g�p
	{
		// ���e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_B) )
		{
			enemys.push_back(new Chara_EnemyBomb(32.0f, 32.0f, 32,
												 GetRand(3) + 2.0f, 2, 20, enemyBombGH));
		}

		// �e�G�l�~�[
		if ( CheckHitKey(KEY_INPUT_A) )
		{
			enemys.push_back(new Chara_EnemyGun(32.0f, 32.0f, 32,
												 GetRand(3) + 2.0f, 2, 20, enemyGunGH));
		}
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(player->GetPosX(), player->GetPosY(),
						  &*shakeAddX, &*shakeAddY);
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
		// �G�ƃv���C���[�̔���
		// ���������������Ă��ăv���C���[���G�̌���ǂ�������ꍇ�A�G�͐i��
		//if ( enemys[i]->GetIsAlive() && player->GetIsAlive()
		//	&& Utility::IsCircleCollision(
		//		enemys[i]->GetPosX(),
		//		enemys[i]->GetPosY(),
		//		enemys[i]->GetRadius() - 8,
		//		player->GetPosX(),
		//		player->GetPosY(),
		//		player->GetRadius() - 8
		//	) )
		//	if ( !enemys[i]->GetIsLeftWard() && !player->GetIsLeftWard()
		//		&& enemys[i]->GetPosX() > player->GetPosX()
		//		|| enemys[i]->GetIsLeftWard() && player->GetIsLeftWard()
		//		&& enemys[i]->GetPosX() < player->GetPosX() )
		//	{
		//		player->CharactersCollision();
		//		player->CharaJump();
		//	}
		//	else
		//	{
		//		player->CharaJump();
		//		player->CharactersCollision();
		//		enemys[i]->CharactersCollision();
		//	}

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

	// �G�l�~�[�U��
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->WeaponManager(electricGunGH);
	}
}

// �U���̓����蔻��
void Chara_Manager::AttackCollision()
{
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// �G�l�~�[�ƃv���C���[�̍U���Ƃ̓����蔻��
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( enemys[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemys[i]->GetPosX(),
										   enemys[i]->GetPosY(),
										   enemys[i]->GetRadius() - 8,
										   player->GetGunPosX(j),
										   player->GetGunPosY(j),
										   player->GetGunRadius(j) - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
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
	// �v���C���[
	player->Draw(shakeX, shakeY);

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 100, GetColor(255, 255, 255), "B�L�[�ŃG�l�~�[���� �G�l�~�[�̐�:%d", enemys.size());
}