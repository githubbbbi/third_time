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
	shotBulletNum = 0;
	isRelease = false;
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
	shotBulletNum = 0;
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

	// --- ��������� ---//
	// Chara_Player.h��bool�^��isRelease������āA2�i�W�����v��h����
	// InputKey::frameCount��static�Ő錾����Ă邩��A�֐��g�킸�ɌĂяo���Ă�
	// frameCount�̊֐���InputKey.h�ɗp�ӂ͂��Ă邩��A�K�v��������֐��ɂ��Ă�
	// �t���[���̍ő�l�ƃt���[��������l�̕ϐ�������ĂȂ�����A����Ăق����i�ǂ��ɍ��΂������킩��Ȃ��Ăł��ĂȂ��j
	// �ꉞ�A�o�����X�݂Ȃ��獡�̒l�ɂ��Ă邯�ǁA�������Ă�����ď���ɕς��đS�R������

	// �W�����v
	if ( InputKey::IsKeyInputNow(e_KEY_JUMP) ||
		InputPad::IsPadInputNow(e_PAD_JUMP) )
	{
		// �W�����v�̏�����
		if ( !isJump )
		{
			InputKey::frameCount[e_KEY_JUMP] = 0; // InputKey::ResetFrame(e_KEY_JUMP)�ł��ł���
			isRelease = false;
			isJump = true;
		}

		// �W�����v�̍X�V����
		if ( isJump )
		{
			InputKey::frameCount[e_KEY_JUMP]++;

			// �L�[�����Ă��Ȃ���΁A�t���[���J�E���g���|�����l��������
			if ( !isRelease && InputKey::frameCount[e_KEY_JUMP] < 3 )
			{
				gravity += JUMP_POWER * (0.6 - (InputKey::frameCount[e_KEY_JUMP] / 10));
			}
			else if ( !isRelease && InputKey::frameCount[e_KEY_JUMP] < 9)
			{
				gravity += JUMP_POWER * 0.1;
			}
		}
	}
	// �W�����v���ɃL�[�������ꂽ���̏����i2�i�W�����v�̑j�~)
	else if ( InputKey::IsKeyInputRelease(e_KEY_JUMP) ||
			InputPad::IsPadInputRelease(e_PAD_JUMP) )
	{
		if ( isJump )
		{
			isRelease = true;
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

	// �������e������萔�𒴂���
	if ( shotBulletNum >= PLAYER_CONSUMPTION_BULLET_NUM )
	{
		// HP����
		hp -= 2;
		shotBulletNum = 0;
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
			else if ( chargeTimer < 60 * 12 )
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
		// �������e���𑝂₷
		shotBulletNum++;
		return true;
	}

	return false;
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		// �`���[�W���͓����Ȃ�
		if ( chargeTimer <= 0 )
		{
			Move();
		}

		HpManager();

		// �����Œ�{�^����������Ă��Ȃ�
		if ( !InputKey::IsKeyInputNow(e_KEY_FIXED_DIRECTION) &&
			!InputPad::IsPadInputNow(e_PAD_FIXED_DIRECTION) )
		{
			ChangeGraphicDirection();
		}
	}
}

// �`�揈��
void Chara_Player::Draw(float shakeX, float shakeY)
{
	// �v���C���[
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY), 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "inputPadX:%d%", InputPad::inputX);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "frameCount:%.2f", InputKey::frameCount[e_KEY_JUMP]);
}