#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"
#include "../Resource/Graphic.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{
}

// �W�����v����
void Chara_EnemyBase::Jump()
{
	if ( x != oldX )
	{
		return;
	}

	// �ڂ̑O�ɏc1�u���b�N�����邩�^��Ƀu���b�N���Ȃ��ꍇ�̂݃W�����v����
	if ( Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_NONE &&
		((Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width + 1, y - CHIP_SIZE) == e_MAP_NONE) ||
		 (Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x - width - 1, y - CHIP_SIZE) == e_MAP_NONE)) )
	{
		CharaJump();
	}
}

// �i�s������ς���
void Chara_EnemyBase::ChangeDirection()
{
	if ( x != oldX || isJump || isFall )
	{
		return;
	}

	// �i�ޗ\��̈ʒu�ɏc��2����Ńu���b�N������
	if ( (Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width + 1, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x - width - 1, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1;
	}

	// �ڂ̑O�ɏc1�u���b�N�����邩�^��Ƀu���b�N������
	if ( (Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1;
	}
}

// �摜�̌�����ω�
void Chara_EnemyBase::ChangeGraphicDirection()
{
	if ( x == oldX )
	{
		return;
	}

	// ���ɐi�s�ŉE�����̏ꍇ
	if ( !isLeftWard )
	{
		if ( speed < 0.0f )
		{
			// ��������
			isLeftWard = true;
		}
	}
	// �E�ɐi�s�ō������̏ꍇ
	else
	{
		if ( speed > 0.0f )
		{
			// �E������
			isLeftWard = false;
		}
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