#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
{

}

// �摜�̌�����ω�
void Chara_EnemyBase::ChangeGraphicDirection()
{
	// ���ɐi�s
	if ( x - oldX < 0.0f )
	{
		isLeftWard = true;
	}
	// �E�ɐi�U
	else if ( x - oldX > 0.0f )
	{
		isLeftWard = false;
	}
}

// �V�F�C�N�X�^�[�g
void Chara_EnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp <= 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

// �v���C���[�Ƃ̊ԂɃu���b�N�����邩�T��
bool Chara_EnemyBase::IsBlock(float playerX)
{
	// �G�ƃv���C���[�̊Ԃ̃u���b�N��
	int enemySpace = (int)fabsf(x - playerX) / CHIP_SIZE;

	// �v���C���[�Ƃ̊ԂɃu���b�N�����邩
	for ( int i = 1; i <= enemySpace; i++ )
	{
		// �������̎�
		if ( isLeftWard )
		{
			if ( Stage::GetMapParam(x - (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
		// �E�����̎�
		else
		{
			if ( Stage::GetMapParam(x + (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
	}

	return false;
}

// �G���m�̓����蔻��
void Chara_EnemyBase::EnemiesCollision()
{

}