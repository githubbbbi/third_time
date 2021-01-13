#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Utility/Utility.h"

const int E_BOMB_WIDTH = 50;
const int E_BOMB_HEIGHT = 50;
const float E_BOMB_NORMAL_SPEED = 1.0f;
const float E_BOMB_DASH_SPEED = 8.0f;

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
		(isLeftWard && x > playerX || !isLeftWard && x < playerX) )
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
}

// �ړ�
void Chara_EnemyBomb::Move(float playerX, float playerY, bool isPlayerAlive)
{
	ChangeDirection();
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// �X�V����
void Chara_EnemyBomb::Update(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
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
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
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