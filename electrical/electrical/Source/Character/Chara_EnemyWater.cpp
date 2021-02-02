#include "DxLib.h"
#include <algorithm>
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EW_WIDTH = 50;
const int EW_HEIGHT = 50;
const int EW_BULLET_INTERVAL = 70;
const int EW_MOTION[e_EW_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 }
};

Chara_EnemyWater::Chara_EnemyWater(float x, float y, int radius, int width, int height,
								   float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
{
	bulletInterval = 0;
	bulletSpeed = 0.0f;
}

Chara_EnemyWater::~Chara_EnemyWater()
{
	// ���e
	for ( int i = waterGun.size() - 1; i >= 0; i-- )
	{
		delete waterGun[i];
		waterGun.erase(waterGun.begin() + i);
	}
}

// �ړ�
void Chara_EnemyWater::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;
	moveY = 0.0f;

	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// ���폈���Ǘ�
void Chara_EnemyWater::WeaponManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// �e�̃C���^�[�o���𑪂�J�E���g
	if ( isAlive )
	{
		bulletInterval++;
	}

	// �C���^�[�o���̏�����
	if ( bulletInterval > EW_BULLET_INTERVAL || isCBlinking )
	{
		bulletInterval = 0;
	}

	// ����
	if ( bulletInterval == EW_BULLET_INTERVAL )
	{
		double a = (double)x - playerX;
		double distance = sqrt(a * a);

		//�@�v���C���[�ƓG�̋����ɂ���āA�e�̃X�s�[�h��ύX����
		if ( distance > 500 )
		{
			bulletSpeed = 15.0f;
		}
		else if ( distance > 300 )
		{
			bulletSpeed = 10.0f;
		}
		else
		{
			bulletSpeed = 5.0f;
		}

		// �������W
		float xx = 24.0f;
		if ( isLeftWard )
		{
			xx *= -1.0f;
		}

		// �򋗗�
		float flightDistance = 100.0f;
		waterGun.push_back(new Weapon_WaterGun(x + xx, y + 8.0f,
											   16,
											   bulletSpeed, GRAVITY,
											   flightDistance, 0,
											   isLeftWard));

		isAttack = true;
	}

	// ���e
	for ( unsigned int i = 0; i < waterGun.size(); i++ )
	{
		waterGun[i]->Update();
	}

	// ���e�폜
	for ( int i = waterGun.size() - 1; i >= 0; i-- )
	{
		if ( !waterGun[i]->GetIsAlive() )
		{
			// �U�����W�����Z�b�g
			attackX = 0.0f;
			attackY = 0.0f;

			delete waterGun[i];
			waterGun.erase(waterGun.begin() + i);
		}
	}
}

// �U���Ǘ�
void Chara_EnemyWater::AttackManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// �v���C���[�ƈ�ԋ������߂����̂���בւ��A�擪�ɂ����Ă���
	std::sort(waterGun.begin(), waterGun.end(),
			  [playerX, playerY](Weapon_WaterGun *a, Weapon_WaterGun *b)
	{
		return fabsf(playerX - a->GetPosX()) < fabsf(playerX - b->GetPosX()) &&
			fabsf(playerY - a->GetPosY()) < fabsf(playerY - b->GetPosY());
	});

	if ( waterGun.size() <= 0 )
	{
		return;
	}

	attackX = waterGun[0]->GetPosX();;
	attackY = waterGun[0]->GetPosY();;
	attackRadius = waterGun[0]->GetRadius();
	isAttackLeftWard = waterGun[0]->GetIsLeftWard();
}

// ������ύX
void Chara_EnemyWater::ChangeDirection(float playerX)
{
	if ( x == playerX )
	{
		return;
	}

	if ( x > playerX )
	{
		// ��������
		isLeftWard = true;
	}
	else
	{
		// �E������
		isLeftWard = false;
	}
}

// ���
void Chara_EnemyWater::State()
{
	// �ҋ@
	if ( moveX == 0.0f && moveY == 0.0f )
	{
		state = e_EW_STATE_IDLE;
	}

	// �U��
	if ( isAttack )
	{
		state = e_EW_STATE_ATTACK;
	}

	// �_���[���󂯂�(�F�_�Œ�)
	if ( isCBlinking )
	{
		state = e_EW_STATE_RECIEVE_DAMAGE;
	}
}

// �X�V����
void Chara_EnemyWater::Update(float playerX, float playerY,
							  int screenX, int screenY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move();
		ChangeDirection(playerX);
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EW_MOTION, 0.0f, 0.0f);
	}

	WeaponManager(playerX, playerY, isPlayerAlive);
	AttackManager(playerX, playerY, isPlayerAlive);

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyWater::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// ���e
	for ( unsigned int i = 0; i < waterGun.size(); i++ )
	{
		waterGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyWater(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g
void Chara_EnemyWater::HitAttack()
{
	if ( waterGun.size() <= 0 )
	{
		return;
	}

	waterGun[0]->Hit();
}