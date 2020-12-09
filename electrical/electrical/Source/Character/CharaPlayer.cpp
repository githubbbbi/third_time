#include "DxLib.h"
#include "Chara_Player.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(int x, int y, int radius,
						   int speed, int hp, int graphHandle):
	CharaBase(x, y, radius, speed, hp, graphHandle)
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
	moveX = 0;
	moveY = 0;

	hpTimer = 0;
	chargeTimer = 0;
}

// �ړ�
void Chara_Player::Move()
{
	// �ړ��ʏ�����
	moveX = 0;
	moveY = 0;

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
		isJump = true;
	}

	// �ړ��ʉ��Z
	x += moveX;
	y += moveY;

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
bool Chara_Player::HpCharge()
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

		if ( chargeTimer % HP_CHARGE_TIME == 0 )
		{
			// HP�㏸
			hp++;
		}

		// �`���[�W����HP�͌������Ȃ�
		hpTimer = 0;

		return true;
	}

	chargeTimer = 0;

	return false;
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		// �`���[�W���͈ړ��s��
		if ( !HpCharge() )
		{
			Move();
		}

		ChangeGraphicDirection();
		HpDcrease();

		// HP�͍ő�l�𒴂��Ȃ�
		if ( hp > MAX_HP )
		{
			hp = 100;
		}
	}
}

// �`�揈��
void Chara_Player::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d �U���{�^���������Ń`���[�W", hp);
}