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
}

Chara_Player::~Chara_Player()
{

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

	// �����L�[/�A�i���O�X�e�B�b�N�ł̍��E�ړ�
	moveX += speed * (InputPad::inputX / 1000.0f);

	// ����ȊO�ł̍��E�ړ�
	if ( InputPad::inputX == 0 &&
		InputPad::inputY == 0 )
	{
		// ���ړ�
		if ( InputKey::IsKeyInputNow(e_KEY_LEFT) ||
			InputPad::IsPadInputNow(e_PAD_LEFT) )
		{
			moveX += speed * (InputPad::inputX / 1000);
		}

		//�E�ړ�
		if ( InputKey::IsKeyInputNow(e_KEY_RIGHT) ||
			InputPad::IsPadInputNow(e_PAD_RIGHT) )
		{
			moveX += speed * (InputPad::inputX);
		}
	}

	// �_�b�V��
	if ( InputKey::IsKeyInputBarrage(e_KEY_LEFT) ||
		InputKey::IsKeyInputBarrage(e_KEY_RIGHT) ||
		InputPad::IsPadInputBarrage(e_PAD_LEFT) ||
		InputPad::IsPadInputBarrage(e_PAD_RIGHT) )
	{
		speed = DASH_SPEED;
	}
	// �_�b�V�����͂��Ȃ���Βʏ�X�s�[�h
	else if ( !InputKey::IsKeyInputNow(KEY_INPUT_LEFT) &&
			 !InputKey::IsKeyInputNow(KEY_INPUT_RIGHT) &&
			 !InputPad::IsPadInputNow(PAD_INPUT_LEFT) &&
			 !InputPad::IsPadInputNow(PAD_INPUT_RIGHT) )
	{
		speed = NORMAL_SPEED;
	}

	// �W�����v
	if ( InputKey::IsKeyInputTrigger(e_KEY_JUMP) ||
		InputPad::IsPadInputTrigger(e_PAD_JUMP) )
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
			else if ( chargeTimer < 60 * 9 )
			{
				chargeTimer += 3;
			}
			else if(chargeTimer < 60 * 12)
			{
				chargeTimer += 5;
			}
			else
			{
				chargeTimer += 6;
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

	// 0�ȉ��ɂ��Ȃ�Ȃ�
	if ( hp < 0 )
	{
		hp = 0;
	}
}

// �U��
bool Chara_Player::IsAttack()
{
	// ���S���͍U���ł��Ȃ�
	if ( !isAlive )
	{
		return false;
	}

	if ( InputKey::IsKeyInputTrigger(e_KEY_ATTACK) ||
		InputPad::IsPadInputTrigger(e_PAD_ATTACK) )
	{
		// HP����
		hp -= 2;// �̂��ɒ萔�����܂�

		return true;
	}

	return false;
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		HpManager();
		ChangeGraphicDirection();
	}
}

// �`�揈��
void Chara_Player::Draw()
{
	// �v���C���[
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "inputPadX:%d%", InputPad::inputX);
}