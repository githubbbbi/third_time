#include "DxLib.h"
#include <algorithm>
#include "Chara_EnemyElectric.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EE_WIDTH = 50;
const int EE_HEIGHT = 50;
const float EE_NORMAL_SPEED = 2.0f;
const int EE_BULLET_INTERVAL = 70;
const int EE_MOTION[e_EE_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 }
};

Chara_EnemyElectric::Chara_EnemyElectric(float x, float y, int radius, int width, int height,
										 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
{
	shotBulletNum = 0;
	bulletInterval = 0;
	shotLength = 0;
	isTargetLock = false;
}

Chara_EnemyElectric::~Chara_EnemyElectric()
{
	// �d�C�e
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// �����ړ�
void Chara_EnemyElectric::AutoMove(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isKnockBack )
	{
		return;
	}

	// ������
	moveX = 0.0f;
	moveY = 0.0f;

	// ���e�G�l�~�[�Ɠ������}�b�v�`�b�v�ł̍��W��
	int enemyMapY = (int)y / CHIP_SIZE;
	int playerMapY = (int)playerY / CHIP_SIZE;

	if ( isPlayerAlive )
	{
		if ( shotLength == 0 )
		{
			shotLength = GetRand(150) + 100;
		}

		// �˒����Ŏ~�܂� �ԂɃu���b�N������΂Ƃ܂�Ȃ�
		if ( fabsf(playerX - x + radius) >= shotLength || IsBlock(playerX) )
		{
			moveX += speed;

			// �˒��O�ł͌����Ȃ�

			isTargetLock = false;

			// �W�����v
			Jump();
		}
		// �����Ⴄ�ꍇ�Ȃ�A�˒����ł��i��
		else if ( enemyMapY != playerMapY )
		{
			moveX += speed;

			// �˒��O�ł͌����Ȃ�
			isTargetLock = false;
		}
		else
		{
			// �˒����ŁAy���W�������Ȃ猂��
			isTargetLock = true;
		}

		// �W�I�ɂȂ�����A�v���C���[��ǂ�������i���]������)
		if ( isTargetLock )
		{
			// �v���C���[���E�ŁA�E�������Ă���ꍇ�A�������ɕς���
			if ( playerX < x && !isLeftWard )
			{
				speed *= -1;
				if ( speed < 0 )
				{
					isLeftWard = true;
				}
			}

			if ( playerX > x && isLeftWard )
			{
				speed *= -1;
				if ( speed > 0 )
				{
					isLeftWard = false;
				}
			}
		}
	}

	// �����Ă���ꍇ�����������Ă��Ȃ�
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		isAttack = false;
	}

	// �v���C���[������ł�ꍇ�́A�e�����Ȃ�
	if ( !isPlayerAlive )
	{
		isTargetLock = false;
	}
}

// �ړ�
void Chara_EnemyElectric::Move(float playerX, float playerY,
							   int screenX, int screenY, bool isPlayerAlive)
{
	ChangeDirection(screenX, screenY);
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �U�������̊Ǘ�
void Chara_EnemyElectric::WeaponManager()
{
	// �e�̃C���^�[�o���𑪂�J�E���g
	if ( isAlive )
	{
		bulletInterval++;
	}

	// �C���^�[�o���̏�����
	if ( bulletInterval > EE_BULLET_INTERVAL || isCBlinking )
	{
		bulletInterval = 0;
	}

	// ����
	if ( bulletInterval == EE_BULLET_INTERVAL && isTargetLock )
	{
		// �򋗗�
		float flightDistance = 100.0f;
		electricGun.push_back(new Weapon_ElectricGun(x, y + 8.0f,
													 16,
													 EG_SPEED, 0.0f,
													 flightDistance, 2,
													 isLeftWard));
		isAttack = true;
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
			// �U�����W�����Z�b�g
			attackX = 0.0f;
			attackY = 0.0f;

			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}

	}
}

// �U���Ǘ�
void Chara_EnemyElectric::AttackManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// �v���C���[�ƈ�ԋ������߂����̂���בւ��A�擪�ɂ����Ă���
	std::sort(electricGun.begin(), electricGun.end(),
			  [playerX, playerY](Weapon_ElectricGun *a, Weapon_ElectricGun *b)
	{
		return fabsf(playerX - a->GetPosX()) < fabsf(playerX - b->GetPosX()) &&
			fabsf(playerY - a->GetPosY()) < fabsf(playerY - b->GetPosY());
	});

	if ( electricGun.size() <= 0 )
	{
		return;
	}

	attackX = electricGun[0]->GetPosX();
	attackY = electricGun[0]->GetPosY();
	attackRadius = electricGun[0]->GetRadius();
	isAttackLeftWard = electricGun[0]->GetIsLeftWard();
}

// ���
void Chara_EnemyElectric::State()
{
	// �ҋ@
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		// ����
		state = e_EE_STATE_WALK;
	}

	// �W�����v
	if ( isJump || isFall )
	{
		state = e_EE_STATE_JUMP;
	}

	// �U��
	if ( isAttack )
	{
		state = e_EE_STATE_ATTACK;
	}

	// �_���[���󂯂�(�F�_�Œ�)
	if ( isCBlinking )
	{
		state = e_EE_STATE_RECIEVE_DAMAGE;
	}
}

// �X�V����
void Chara_EnemyElectric::Update(float playerX, float playerY,
								 int screenX, int screenY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, screenX, screenY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EE_MOTION, EE_NORMAL_SPEED, 0.0f);
	}

	WeaponManager();
	AttackManager(playerX, playerY, isPlayerAlive);

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyElectric::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyElectric(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g
void Chara_EnemyElectric::HitAttack()
{
	if ( electricGun.size() <= 0 )
	{
		return;
	}

	electricGun[0]->Hit();
}