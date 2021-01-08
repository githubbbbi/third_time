#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Utility/Utility.h"

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
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
	// �ړ��ʏ�����
	moveX = 0.0f;
	moveY = 0.0f;

	// �i�s�����`�F���W
	ChangeDirection();

	// �ړ�����
	// �G�ƃv���C���[��X���W�����������A�X�s�[�h���_�b�V���ɍ��킹��
	if ( isPlayerAlive && !IsBlock(playerX) &&
		(y == playerY && isLeftWard && playerX < x ||
		 y == playerY && !isLeftWard && playerX > x) )
	{
		if ( speed > 0 )
		{
			speed = E_BOMB_DASH_SPEED;
		}
		else
		{
			speed = -E_BOMB_DASH_SPEED;
		}
	}
	// �Ⴄ���A�X�s�[�h���m�[�}���ɖ߂�
	else
	{
		if ( speed > 0 )
		{
			speed = E_BOMB_NORMAL_SPEED;
		}
		else
		{
			speed = -E_BOMB_NORMAL_SPEED;
		}

		// �W�����v
		Jump();
	}

	moveX += speed;
	CharaMove((float)width, (float)height);
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
		ColorBlinking(0.0f, 255.0f, 255.0f, 2);
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
		SetDrawBright(255, 255, 255);
	}
}

// �U���q�b�g
void Chara_EnemyBomb::HitAttack(float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		hp = 0;
	}
}