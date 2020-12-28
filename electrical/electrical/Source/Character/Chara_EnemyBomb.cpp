#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius,
								 float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

Chara_EnemyBomb::~Chara_EnemyBomb()
{

}

// ����������
void Chara_EnemyBomb::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;
}

// �ړ�
void Chara_EnemyBomb::Move(float playerX, float playerY)
{
	moveX = 0.0f;
	moveY = 0.0f;

	// ��������
	{
		// �ړ�����
		// �G�ƃv���C���[��X���W�����������A�X�s�[�h���_�b�V���ɍ��킹��
		if ( y == playerY)
		{
			if (speed > 0)
			{
				speed = DASH_SPEED;
			}
			else
			{
				speed = -DASH_SPEED;
			}
		}
		// �Ⴄ���A�X�s�[�h���m�[�}���ɖ߂�
		else
		{
			if (speed > 0)
			{
				speed = NORMAL_SPEED;
			}
			else
			{
				speed = -NORMAL_SPEED;
			}

			// X���W�ɕω����Ȃ��Ȃ������ɃW�����v����
			if (x == oldX)
			{
				CharaJump();
			}

			// ��ʊO�ɍs�������ȂƂ��A�i�ޗ\��̈ʒu��2����Ńu���b�N���������ꍇ�A������ς���
			if (x - radius < 0 || x + radius > WIN_WIDTH ||
				Stage::GetMapParam(x + radius + 1, y) == e_MAP_BLOCK &&
				Stage::GetMapParam(x + radius + 1, y - CHIP_SIZE) == e_MAP_BLOCK ||
				Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK &&
				Stage::GetMapParam(x - radius - 2, y - CHIP_SIZE) == e_MAP_BLOCK)
			{
				speed *= -1;
			}
		}

		moveX += speed;
	}
	// �����܂�

	CharaMove();
}

// �X�V����
void Chara_EnemyBomb::Update(float playerX, float playerY,
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
void Chara_EnemyBomb::Draw(float shakeX, float shakeY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY),
					  1.0, 0.0, graphHandle, true, isLeftWard);
	}
}

// �U�������Ǘ�
void Chara_EnemyBomb::WeaponManager(int electricGunGH)
{

}