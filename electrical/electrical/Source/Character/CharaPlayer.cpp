#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(float x, float y, int radius,
						   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;

	bulletGraphHandle = LoadGraph("Resource/Graphic/Bullet/bullet.png");
}

Chara_Player::~Chara_Player()
{

}

// �e�\���̂̃R���X�g���N�^
Chara_Player::Bullet::Bullet(float x, float y, int radius, float speed, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->graphHandle = graphHandle;

	isAlive = true;
}

// ����������
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	hpTimer = 0;
	chargeTimer = 0;
}

// �ړ�
void Chara_Player::Move()
{
	// �ړ��ʏ�����
	moveX = 0.0f;
	moveY = 0.0f;

	// ���ړ�
	if ( InputKey::IsKeyInputNow(e_KEY_LEFT) ||
		InputPad::IsPadInputNow(e_PAD_LEFT) )
	{
		moveX -= speed;
	}

	//�E�ړ�
	if ( InputKey::IsKeyInputNow(e_KEY_RIGHT) ||
		InputPad::IsPadInputNow(e_PAD_RIGHT) )
	{
		moveX += speed;
	}

	// �W�����v
	if ( InputKey::IsKeyInputNow(e_KEY_JUMP) ||
		InputPad::IsPadInputNow(e_PAD_JUMP) )
	{
		// �W�����v���łȂ�
		if ( !isJump )
		{
			gravity = JUMP_POWER;
			isJump = true;
		}
	}

	CharaMove();

	// ��ʓ��ɂƂǂ܂�(X�����ɂ��Ă̂�)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// HP(�o�b�e���[)����
void Chara_Player::HpDcrease()
{
	hpTimer++;
	if ( hpTimer > HP_DCREASE_TIME )
	{
		// HP����
		hp--;

		// �^�C�}�[���Z�b�g
		hpTimer = 0;
	}
}

// HP(�o�b�e���[)�`���[�W
void Chara_Player::HpCharge()
{
	// �ړ����łȂ�
	if ( moveX == 0.0f && moveY == 0.0f && !isJump )
	{
		if ( InputKey::IsKeyInputNow(e_KEY_ATTACK) ||
			InputPad::IsPadInputNow(e_PAD_ATTACK) )
		{
			// ��莞�ԃ`���[�W�Ń`���[�W�ʂ�����
			if ( chargeTimer < 60 * 3 )
			{
				chargeTimer++;
			}
			else if ( chargeTimer < 60 * 6 )
			{
				chargeTimer += 2;
			}
			else
			{
				chargeTimer += 3;
			}

			// HP�㏸
			if ( chargeTimer % HP_CHARGE_TIME == 0 )
			{
				hp++;
			}

			// �`���[�W����HP�͌������Ȃ�
			hpTimer = 0;

			return;
		}
	}

	chargeTimer = 0;
}

// HP�Ǘ�
void Chara_Player::HpManager()
{
	HpDcrease();
	HpCharge();
	HpZero();

	// HP�͍ő�l�𒴂��Ȃ�
	if ( hp > PLAYER_MAX_HP )
	{
		hp = 100;
	}
}

// �U��
void Chara_Player::Attack()
{
	if ( InputKey::IsKeyInputTrigger(e_KEY_ATTACK) ||
		InputPad::IsPadInputTrigger(e_PAD_ATTACK) )
	{
		bullets.push_back(new Bullet(x, y, 16, 15, bulletGraphHandle));
	}
}

// �e�̍X�V����
void Chara_Player::Bullet::Update()
{
	x -= speed;

	if ( x + radius<0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		HpManager();
		Attack();
		ChangeGraphicDirection();

		// �e
		for ( int i = 0; i < bullets.size(); i++ )
		{
			bullets[i]->Update();
		}
	}
}

// �`�揈��
void Chara_Player::Draw()
{
	// �e
	for ( int i = 0; i < bullets.size(); i++ )
	{
		if ( bullets[i]->isAlive )
		{
			DrawRotaGraph((int)bullets[i]->x, (int)bullets[i]->y,
						  1.0, 0.0, bullets[i]->graphHandle, true);
		}
	}

	// �v���C���[
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
}