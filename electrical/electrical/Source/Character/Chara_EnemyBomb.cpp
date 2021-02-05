#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EB_WIDTH = 50;
const int EB_HEIGHT = 50;
const float EB_NORMAL_SPEED = 1.0f;
const float EB_DASH_SPEED = 8.0f;
const int EB_MOTION[e_EB_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 }
};

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
{

}

// �����ړ�
void Chara_EnemyBomb::AutoMove(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isKnockBack )
	{
		return;
	}

	// ������
	moveX = 0.0f;
	moveY = 0.0f;

	// ���W���}�b�v�`�b�v�ł̍��W�ɕϊ�
	int enemyMapY = (int)y / CHIP_SIZE;
	int playerMapY = (int)playerY / CHIP_SIZE;

	// �ړ�����
	// �G�ƃv���C���[��y���W�����������A�X�s�[�h���_�b�V���ɍ��킹��
	if ( isPlayerAlive && !IsBlock(playerX) &&
		(enemyMapY == playerMapY) &&
		(isLeft && x > playerX || !isLeft && x < playerX) )
	{
		if ( speed > 0 )
		{
			speed = EB_DASH_SPEED;
		}
		else
		{
			speed = -EB_DASH_SPEED;
		}

		isAttack = true;
	}
	// �Ⴄ���A�X�s�[�h���m�[�}���ɖ߂�
	else
	{
		if ( speed > 0 )
		{
			speed = EB_NORMAL_SPEED;
		}
		else
		{
			speed = -EB_NORMAL_SPEED;
		}

		isAttack = false;

		// �W�����v
		Jump();
	}

	moveX += speed;
}

// �ړ�
void Chara_EnemyBomb::Move(float playerX, float playerY,
						   int screenX, int screenY, bool isPlayerAlive)
{
	ChangeDirection(screenX, screenY);
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �U���Ǘ�
void Chara_EnemyBomb::AttackManager(bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	if ( isAttack )
	{
		attackX = x;
		attackY = y;
		attackRadius = radius;
		isAttackLeft = isLeft;
	}
	else
	{
		attackX = 0.0f;
		attackY = 0.0f;
	}
}

// ���
void Chara_EnemyBomb::State()
{
	// ����
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		state = e_EB_STATE_WALK;
	}

	// �W�����v
	if ( isJump || isFall )
	{
		state = e_EB_STATE_JUMP;
	}

	// �U��
	if ( isAttack )
	{
		state = e_EB_STATE_ATTACK;
	}

	// �_���[���󂯂�(�F�_�Œ�)
	if ( isCBlinking )
	{
		state = e_EB_STATE_RECIEVE_DAMAGE;
	}
}

// �X�V����
void Chara_EnemyBomb::Update(float playerX, float playerY,
							 int screenX, int screenY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, screenX, screenY, isPlayerAlive);
		AttackManager(isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EB_MOTION, EB_NORMAL_SPEED, EB_DASH_SPEED);
	}

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX + displaceX,
					  (int)(y + shakeY) - scrollY + displaceY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyBomb(graphIndex), true, isLeft);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g(�ːi)
void Chara_EnemyBomb::HitAttack()
{
	if ( isAlive )
	{
		hp = 0;
	}
}