#include "DxLib.h"
#include "Chara_EnemyGun.h"
#include "../Define/Define.h"

Chara_EnemyGun::Chara_EnemyGun(float x, float y, int radius, 
							   float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

Chara_EnemyGun::~Chara_EnemyGun()
{

}

// ����������
void Chara_EnemyGun::Initialize()
{

}

// �ړ�����
void Chara_EnemyGun::Move(float playerX, float playerY)
{
	moveX = 0.0f;
	moveY = 0.0f;

	// ��������
	{
		if ( x - radius < 0 || x + radius > WIN_WIDTH )
		{
			speed *= -1;
		}

		moveX += speed;

		// �W�����v����Ƃ�
		CharaJump();
	}
	// �����܂�

	CharaMove();
}

// �X�V����
void Chara_EnemyGun::Update(float playerX, float playerY, 
							float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY);
		ChangeGraphicDirection();
		HpZero();
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}
}

// �`�揈��
void Chara_EnemyGun::Draw(float shakeX, float shakeY)
{
	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw();
	}

	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY),
					  1.0, 0.0, graphHandle, true, isLeftWard);
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
	// ������
	// �d�C�e�̍X�V����

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