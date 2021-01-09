#include "DxLib.h"
#include "Chara_EnemyGun.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"

Chara_EnemyGun::Chara_EnemyGun(float x, float y, int radius, int width, int height,
	float speed, int hp, int attackPower, int graphHandle) :
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
{
	shotBulletNum = 0;
	bulletInterval = 0;
	isTargetLock = false;
}

Chara_EnemyGun::~Chara_EnemyGun()
{
	// �d�C�e
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// ����������
void Chara_EnemyGun::Initialize()
{

}

void Chara_EnemyGun::Move(float playerX, float playerY, bool isPlayerAlive)
{
	// ������
	moveX = 0.0f;
	moveY = 0.0f;

	// �i�s�����`�F���W
	ChangeDirection();

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
		else if (enemyMapY!= playerMapY )
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
				if (speed < 0 )
				{
					isLeftWard = true;
				}
			}
			
			if ( playerX > x && isLeftWard )
			{
				speed *= -1;

				if (speed > 0 )
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

	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �X�V����
void Chara_EnemyGun::Update(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 2);
	}

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyGun::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
			1.0, 0.0, graphHandle, true, isLeftWard);
		SetDrawBright(255, 255, 255);
	}

}

// �U���q�b�g
void Chara_EnemyGun::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// �U�������̊Ǘ�
void Chara_EnemyGun::WeaponManager(int electricGunGH)
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
		electricGun.push_back(new ElectricGun(x, y,
			16, 10.0f,
			isLeftWard,
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

// �d�C�e�̗v�f��
unsigned int Chara_EnemyGun::GetGunSize()
{
	return electricGun.size();
}

// �d�C�e��X���W�擾
float Chara_EnemyGun::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// �d�C�e��Y���W�擾
float Chara_EnemyGun::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// �d�C�e��radius�擾
int Chara_EnemyGun::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}