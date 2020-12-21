#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(float x, float y, int radius,
						   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;
	shotBulletNum = 0;
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

	// �p�b�h���o�[�̓��͏����擾
	static int padInputX, padInputY;
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// �����L�[/�A�i���O�X�e�B�b�N�ł̍��E�ړ�
	moveX += speed * (padInputX / 1000.0f);

	// ����ȊO�ł̍��E�ړ�
	if ( InputManager::GetPadInputX == 0 &&
		InputManager::GetPadInputY == 0 )
	{
		// ���ړ�
		if ( InputManager::IsInputNow(e_MOVE_LEFT) )
		{
			moveX += speed * (padInputX / 1000);
		}

		//�E�ړ�
		if ( InputManager::IsInputNow(e_MOVE_RIGHT) )
		{
			moveX += speed * (padInputX);
		}
	}

	// �_�b�V��
	if ( InputManager::IsInputBarrage(e_MOVE_LEFT) ||
		InputManager::IsInputBarrage(e_MOVE_RIGHT) )
	{
		speed = DASH_SPEED;
	}
	// �_�b�V�����͂��Ȃ���Βʏ�X�s�[�h
	else if ( !InputManager::IsInputNow(e_MOVE_LEFT) &&
			 !InputManager::IsInputNow(e_MOVE_RIGHT) )
	{
		speed = NORMAL_SPEED;
	}

	// �W�����v
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// �W�����v�̏�����
		if ( !isJump && !isFall )
		{
			gravity = JUMP_POWER;
			isJump = true;
		}
	}

	// �W�����v�㏸�����ɃL�[�������ꂽ�ꍇ�W�����v�𒆎~
	if ( isJump && gravity < 0.0f )
	{
		if ( InputManager::IsInputNot(e_JUMP) )
		{
			gravity = JUMP_POWER / 2.0f;
			isJump = false;
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
		if ( InputManager::IsInputNow(e_ATTACK) )
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

	if ( InputManager::IsInputTrigger(e_ATTACK) )
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
		if ( !InputManager::IsInputNow(e_FIXED_DIRECTION) )
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
}