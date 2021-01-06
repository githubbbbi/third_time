#include "Chara_EnemyBase.h"
#include"../stage/stage.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	blockFlag = false;
	enemySpace = 0.0f;
}

// �V�F�C�N�X�^�[�g
void Chara_EnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp == 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

//�G�̓����蔻��
void Chara_EnemyBase::EnemiesCollision()
{

}

// �u���b�N���Ԃɂ��邩�T��
void Chara_EnemyBase::FindBlock(float playerX)
{
	//�G�ƃv���C���[�̊Ԃ̃u���b�N��
	if (x < playerX)
	{
		enemySpace = (playerX - x) / CHIP_SIZE;
	}
	else
	{
		enemySpace = (x - playerX) / CHIP_SIZE;
	}

	//�E�������̃v���C���[�Ƃ̊ԂɃu���b�N�����邩
	for (int i = 0; i < enemySpace; i++)
	{
		if (isLeftWard == false)
		{
			if (Stage::GetMapParam(x + (64 * i), y) == e_MAP_BLOCK)
			{
				blockFlag = true;
			}
		}
		else if (isLeftWard == false)
		{
			if (Stage::GetMapParam(x - (64 * i), y) == e_MAP_BLOCK)
			{
				blockFlag = true;
			}
		}
	}
}
