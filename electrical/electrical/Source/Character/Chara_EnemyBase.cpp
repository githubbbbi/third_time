#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"

const float E_JUMP_POWER = -13.0f;

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{
	this->mapChipX = mapChipX;
	this->mapChipY = mapChipY;
	attackX = 0.0f;
	attackY = 0.0f;
	attackRadius = 0;
	isAttackLeft = isLeft;
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
		CharaJump(E_JUMP_POWER);
	}
}

// �i�s������ς���
void Chara_EnemyBase::ChangeDirection(int screenX, int screenY)
{
	// �X�N���[�����[ ���̔���͗D�悵�čs����
	// ��
	if ( (int)x - width / 2 < screenX - displaceX +
		(displaceX / (screenX / (WIN_WIDTH / 2))) - WIN_WIDTH / 2 )
	{
		x = (float)(screenX - displaceX + (
			displaceX / (screenX / (WIN_WIDTH / 2))) - WIN_WIDTH / 2 + width / 2);
		speed *= -1.0f;
		return;
	}
	// �E
	else if ( (int)x + width / 2 > screenX - displaceX -
			 (displaceX / (screenX / (WIN_WIDTH / 2))) + WIN_WIDTH / 2 )
	{
		x = (float)(screenX - displaceX -
					(displaceX / (screenX / (WIN_WIDTH / 2))) + WIN_WIDTH / 2 - width / 2);
		speed *= -1.0f;
		return;
	}

	// �����Ă��Ȃ��܂��̓W�����v�A�������̎�
	if ( x != oldX || isJump || isFall )
	{
		return;
	}

	// �i�ޗ\��̈ʒu�ɏc��2����Ńu���b�N������
	if ( (Stage::GetMapParam(x + width / 2 + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width / 2 + 1, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width / 2 - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x - width / 2 - 1, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1.0f;
		return;
	}

	// �ڂ̑O�ɏc1�u���b�N�����邩�^��Ƀu���b�N������
	if ( (Stage::GetMapParam(x + width / 2 + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width / 2 - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1.0f;
		return;
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
	if ( !isLeft )
	{
		if ( speed < 0.0f )
		{
			// ��������
			isLeft = true;
		}
	}
	// �E�ɐi�s�ō������̏ꍇ
	else
	{
		if ( speed > 0.0f )
		{
			// �E������
			isLeft = false;
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
		if ( isLeft )
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

int Chara_EnemyBase::GetMapChipX()
{
	return mapChipX;
}

int Chara_EnemyBase::GetMapChipY()
{
	return mapChipY;
}

float Chara_EnemyBase::GetAttackPosX()
{
	return attackX;
}

float Chara_EnemyBase::GetAttackPosY()
{
	return attackY;
}

int Chara_EnemyBase::GetAttackRadius()
{
	return attackRadius;
}

bool Chara_EnemyBase::GetIsAttackLeftWard()
{
	return isAttackLeft;
}