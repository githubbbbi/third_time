#include "DxLib.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int E_WATER_WIDTH = 50;
const int E_WATER_HEIGHT = 50;

Chara_EnemyWater::Chara_EnemyWater(float x, float y, int radius, int width, int height,
								   float speed, int hp, int attackPower):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower)
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

// ����������
void Chara_EnemyWater::Initialize()
{

}

// �ړ�
void Chara_EnemyWater::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;
	moveY = 0.0f;

	CharaMove((float)width / 2.0f, (float)height / 2.0f);
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

// �X�V����
void Chara_EnemyWater::Update(float playerX, float playerY)
{
	if ( isAlive )
	{
		Move();
		ChangeDirection(playerX);
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
	}

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
					  1.0, 0.0, Graphic::GetEnemyWater(), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g
void Chara_EnemyWater::HitAttack(int index)
{
	waterGun[index]->Hit();
}

// ���폈���Ǘ�
void Chara_EnemyWater::WeaponManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// �e�̃C���^�[�o���𑪂�J�E���g
	bulletInterval++;

	// �C���^�[�o���̏�����
	if ( bulletInterval > BULLET_INTERVAL )
	{
		bulletInterval = 0;
	}

	// ����
	if ( bulletInterval == BULLET_INTERVAL )
	{
		double a = (double)x - playerX;
		double b = (double)y - playerY;
		double distance = sqrt(a * a + b * b);

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

		waterGun.push_back(new Weapon_WaterGun(x, y, 16,
											   bulletSpeed,
											   GRAVITY, 0,
											   isLeftWard));
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
			delete waterGun[i];
			waterGun.erase(waterGun.begin() + i);
		}

	}
}

// ���e�̗v�f��
unsigned int Chara_EnemyWater::GetGunSize()
{
	return waterGun.size();
}

// ���e��X���W�擾
float Chara_EnemyWater::GetGunPosX(int index)
{
	return waterGun[index]->GetPosX();
}

// ���e��Y���W�擾
float Chara_EnemyWater::GetGunPosY(int index)
{
	return waterGun[index]->GetPosY();
}

// ���e��radius�擾
int Chara_EnemyWater::GetGunRadius(int index)
{
	return waterGun[index]->GetRadius();
}

// ���e��isLeftWard�擾
bool Chara_EnemyWater::GetIsGunLeftWard(int index)
{
	return waterGun[index]->GetIsLeftWard();
}