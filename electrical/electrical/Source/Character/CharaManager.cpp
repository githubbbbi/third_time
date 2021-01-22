#include "DxLib.h"
#include "Chara_Manager.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Resource/CSV.h"

Chara_Manager::Chara_Manager()
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			spawnData[y][x] = -1;
			isEnemySpawn[y][x] = false;
		}
	}

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
bool Chara_Manager::Initialize()
{
	// �v���C���[
	player->Initialize();

	// �G�l�~�[�͑S�ď��������Ⴄ
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}

	// �t�@�C���ǂݍ���
	if ( !LoadFile() )
	{
		return false;
	}

	return true;
}

// �t�@�C���ǂݍ���
bool Chara_Manager::LoadFile()
{
	// �ǂݍ��ރt�@�C�������i�[����
	char fileName[512];
	sprintf_s(fileName, sizeof(fileName),
			  "Resource/Data/Spawn_Position/enemy_stage%d.csv", 1);

	// �t�@�C�����ǂݍ��߂Ȃ��ꍇ�Afalse
	int *p = (int *)spawnData;
	if ( !CSV::LoadFile(fileName,
						MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// �G�l�~�[�̐���
void Chara_Manager::EnemyGenerate(int screenX, int screenY)
{
	// �X�N���[���ɉf���Ă��镔������
	int mapChipLeft = (screenX - WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipRight = (screenX + WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipTop = (screenY - WIN_HEIGHT / 2) / CHIP_SIZE;
	int mapChipBottom = (screenY + WIN_HEIGHT / 2) / CHIP_SIZE;

	for ( int y = mapChipTop; y < mapChipBottom; y++ )
	{
		for ( int x = mapChipLeft; x < mapChipRight; x++ )
		{
			// �N���Ă�ꍇ�̓X�L�b�v
			if ( isEnemySpawn[y][x] )
			{
				continue;
			}

			// �X�|�[���ʒu
			float spawnX = (float)(x * CHIP_SIZE) + CHARA_SIZE / 2;
			float spawnY = (float)(y * CHIP_SIZE) + CHARA_SIZE / 2;

			switch ( spawnData[y][x] )
			{
				case e_EnemyBomb:
					// ���e�G�l�~�[
					enemys.push_back(new Chara_EnemyBomb(spawnX, spawnY,
														 32, EB_WIDTH, EB_HEIGHT,
														 EB_NORMAL_SPEED, 2, 10, x, y));

					isEnemySpawn[y][x] = true;
					break;

				case e_EnemyElectric:
					// �e�G�l�~�[
					enemys.push_back(new Chara_EnemyElectric(spawnX, spawnY,
															 32, EE_WIDTH, EE_HEIGHT,
															 EE_NORMAL_SPEED, 2, 2, x, y));
					isEnemySpawn[y][x] = true;
					break;

				case e_EnemyWater:
					// ���e�G�l�~�[
					enemys.push_back(new Chara_EnemyWater(spawnX, spawnY,
														  32, EW_WIDTH, EW_HEIGHT,
														  0.0f, 2, 2, x, y));
					isEnemySpawn[y][x] = true;
					break;

				default:
					break;
			}
		}
	}
}

// �G�l�~�[�Ǘ�
void Chara_Manager::EnemyManager(int screenX, int screenY)
{
	// �G�l�~�[�̐���
	EnemyGenerate(screenX, screenY);

	// �X�V����
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	int mapChipLeft = (screenX - WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipRight = (screenX + WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipTop = (screenY - WIN_HEIGHT / 2) / CHIP_SIZE;
	int mapChipBottom = (screenY + WIN_HEIGHT / 2) / CHIP_SIZE;

	// ����
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		// �X�|�[���ʒu���X�N���[���O�̏ꍇ
		if ( (enemys[i]->GetMapChipX() < mapChipLeft ||
			  enemys[i]->GetMapChipX() > mapChipRight) ||
			(enemys[i]->GetMapChipY() < mapChipTop ||
			 enemys[i]->GetMapChipY() > mapChipBottom) )
		{
			isEnemySpawn[enemys[i]->GetMapChipY()][enemys[i]->GetMapChipX()] = false;

			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// �L�����N�^���m�̓����蔻��
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() || player->GetIsInvicible() )
	{
		return;
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			continue;
		}

		// �v���C���[�ƓG�Ƃ̔���
		if ( Utility::IsRectCollision(enemys[i]->GetPosX(),
									  enemys[i]->GetPosY(),
									  enemys[i]->GetWidth(),
									  enemys[i]->GetHeight(),
									  player->GetPosX(),
									  player->GetPosY(),
									  player->GetWidth(),
									  player->GetHeight()) )
		{
			player->ReceiveDamage(2, !player->GetIsLeftWard());
			break;
		}
	}
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
			continue;
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
	DrawFormatString(100, 150, GetColor(255, 255, 255), "�G�l�~�[�̐�:%d", enemys.size());
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
	if ( !player->GetIsAlive() && !player->GetIsExplosion() )
	{
		// ���W���擾
		explosionX = player->GetPosX();
		explosionY = player->GetPosY();

		player->Explosion();

		return true;
	}

	// �G�l�~�[
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemys[i]->GetIsAlive() && !enemys[i]->GetIsExplosion() )
		{
			// ���W���擾
			explosionX = enemys[i]->GetPosX();
			explosionY = enemys[i]->GetPosY();

			enemys[i]->Explosion();

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