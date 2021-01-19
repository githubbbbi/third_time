#include "DxLib.h"
#include "Chara_EnemyElectric.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int E_GUN_WIDTH = 50;
const int E_GUN_HEIGHT = 50;
const float E_GUN_NORMAL_SPEED = 2.0f;
const float E_GUN_DASH_SPEED = 4.0f;

Chara_EnemyElectric::Chara_EnemyElectric(float x, float y, int radius, int width, int height,
										 float speed, int hp, int attackPower):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower)
{
	shotBulletNum = 0;
	bulletInterval = 0;
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

// ����������
void Chara_EnemyElectric::Initialize()
{

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
		// �˒����Ŏ~�܂� �ԂɃu���b�N������΂Ƃ܂�Ȃ�
		if ( playerX - x + radius >= 200 ||
			x - radius - playerX >= 200 || IsBlock(playerX) )
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

	// �v���C���[������ł�ꍇ�́A�e�����Ȃ�
	if ( !isPlayerAlive )
	{
		isTargetLock = false;
	}
}

// �ړ�
void Chara_EnemyElectric::Move(float playerX, float playerY, bool isPlayerAlive)
{
	ChangeDirection();
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �X�V����
void Chara_EnemyElectric::Update(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		AttackMotion();
		State();
		LocalAnimation();
	}

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
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyElectric(), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g
void Chara_EnemyElectric::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// �U�������̊Ǘ�
void Chara_EnemyElectric::WeaponManager()
{
	// �e�̃C���^�[�o���𑪂�J�E���g
	bulletInterval++;

	// �C���^�[�o���̏�����
	if ( bulletInterval > BULLET_INTERVAL )
	{
		bulletInterval = 0;
	}

	// ����
	if ( bulletInterval == BULLET_INTERVAL && isTargetLock )
	{
		electricGun.push_back(new Weapon_ElectricGun(x, y, 16,
													 EG_SPEED,
													 0.0f, 2,
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
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}

	}
}

// �d�C�e�̗v�f��
unsigned int Chara_EnemyElectric::GetGunSize()
{
	return electricGun.size();
}

// �d�C�e��X���W�擾
float Chara_EnemyElectric::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// �d�C�e��Y���W�擾
float Chara_EnemyElectric::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// �d�C�e��radius�擾
int Chara_EnemyElectric::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}

// �d�C�e��isLeftWard�擾
bool Chara_EnemyElectric::GetIsGunLeftWard(int index)
{
	return electricGun[index]->GetIsLeftWard();
}