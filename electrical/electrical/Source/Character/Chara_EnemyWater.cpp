#include "DxLib.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"

Chara_EnemyWater::Chara_EnemyWater(float x, float y, int radius, int width, int height,
									float speed, int hp, int attackPower, int graphHandle) :
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
{
	bulletInterval = 0;
	bulletSpeed = 0.0f;
}

Chara_EnemyWater::~Chara_EnemyWater()
{
	// ���e
	for (int i = waterBullet.size() - 1; i >= 0; i--)
	{
		delete waterBullet[i];
		waterBullet.erase(waterBullet.begin() + i);
	}
}

// ����������
void Chara_EnemyWater::Initialize()
{

}

// �ړ�
void Chara_EnemyWater::Move()
{
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �X�V����
void Chara_EnemyWater::Update(float playerX, float playerY)
{
	if (isAlive)
	{
		Move();

		// ������ς��鏈��
		{
			if (x == playerX)
			{
				//return;
			}

			if (x > playerX)
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

		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 2);
	}

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyWater::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// ���e
	for (unsigned int i = 0; i < waterBullet.size(); i++)
	{
		waterBullet[i]->Draw(scrollX, scrollY);
	}

	if (isAlive)
	{
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
			1.0, 0.0, graphHandle, true, isLeftWard);
		SetDrawBright(255, 255, 255);
	}
}

// �U���q�b�g
void Chara_EnemyWater::HitAttack(int index)
{
	waterBullet[index]->Hit();
}

// ���폈���Ǘ�
void Chara_EnemyWater::WeaponManager(float playerX, float playerY, bool isPlayerAlive, int waterBulletGH)
{
	// �e�̃C���^�[�o���𑪂�J�E���g
	bulletInterval++;

	// �C���^�[�o���̏�����
	if (bulletInterval > BULLET_INTERVAL)
	{
		bulletInterval = 0;
	}

	// ����
	if (bulletInterval == BULLET_INTERVAL && isPlayerAlive)
	{
		double a = (double)x - playerX;
		double b = (double)y - playerY;
		double distance = sqrt(a * a + b * b);

		//�@�v���C���[�ƓG�̋����ɂ���āA�e�̃X�s�[�h��ύX����
		if (distance > 500)
		{
			bulletSpeed = 15.0f;
		}
		else if(distance > 300)
		{
			bulletSpeed = 10.0f;
		}
		else
		{
			bulletSpeed = 5.0f;
		}

		waterBullet.push_back(new WaterBullet(x, y,
			16, bulletSpeed,
			isLeftWard,
			waterBulletGH));
	}

	// ���e
	for (unsigned int i = 0; i < waterBullet.size(); i++)
	{
		waterBullet[i]->Update();
	}

	// ���e�폜
	for (int i = waterBullet.size() - 1; i >= 0; i--)
	{
		if (!waterBullet[i]->GetIsAlive())
		{
			delete waterBullet[i];
			waterBullet.erase(waterBullet.begin() + i);
		}

	}
}

// ���e�̗v�f��
unsigned int Chara_EnemyWater::GetGunSize()
{
	return waterBullet.size();
}

// ���e��X���W�擾
float Chara_EnemyWater::GetGunPosX(int index)
{
	return waterBullet[index]->GetPosX();
}

// ���e��Y���W�擾
float Chara_EnemyWater::GetGunPosY(int index)
{
	return waterBullet[index]->GetPosY();
}

// ���e��radius�擾
int Chara_EnemyWater::GetGunRadius(int index)
{
	return waterBullet[index]->GetRadius();
}
