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
void Chara_EnemyBomb::Move(float playerX, float playerY, bool isPlayerAlive)
{
	moveX = 0.0f;
	moveY = 0.0f;

	blockFlag = false;

	// �u���b�N���Ԃɂ��邩�T��
	FindBlock(playerX);

	// �ړ�����
	// �G�ƃv���C���[��X���W�����������A�X�s�[�h���_�b�V���ɍ��킹��
	if ( isPlayerAlive && !blockFlag &&
		(y == playerY && isLeftWard && playerX < x ||
		 y == playerY && !isLeftWard && playerX > x) )
	{
		if ( speed > 0 )
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
		if ( speed > 0 )
		{
			speed = NORMAL_SPEED;
		}
		else
		{
			speed = -NORMAL_SPEED;
		}

		// �i�ޗ\��̈ʒu��2����Ńu���b�N���������ꍇ�A������ς���
		if (Stage::GetMapParam(x + radius + 2, y) == e_MAP_BLOCK &&
			Stage::GetMapParam(x + radius + 2, y - CHIP_SIZE) == e_MAP_BLOCK ||
			Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK &&
			Stage::GetMapParam(x - radius - 2, y - CHIP_SIZE) == e_MAP_BLOCK)
		{
			speed *= -1;
		}

		// X���W�ɕω����Ȃ��Ȃ������ɃW�����v����
		if (x == oldX)
		{
			CharaJump();
		}
	}

	moveX += speed;

	CharaMove(30.0f, 30.0f);
}

// �X�V����
void Chara_EnemyBomb::Update(float playerX, float playerY, bool isPlayerAlive,
							 float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}
}

// �`�揈��
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
	}
}