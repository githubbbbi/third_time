#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int P_WIDTH = 50;
const int P_HEIGHT = 50;
const float P_NORMAL_SPEED = 3.0f;
const float P_DASH_SPEED = 5.0f;
const int BATTERY_DCREASE_TIME = 60 * 1;
const int BATTERY_CHARGE_TIME = 60 * 1;
const int P_MAX_BATTERY = 100;
const int P_CONSUMPTION_BULLET_NUM = 5;
const int P_MOTION[e_P_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 },
	{ 16, 17, 18, 19 },
	{ 20, 21, 22, 23 },
	{ 24, 25, 26, 27 },
	{ 28, 29, 30, 31 },
	{ 32, 33, 34, 35 },
	{ 36, 37, 38, 39 }
};

Chara_Player::Chara_Player(float x, float y, int radius, int width, int height,
						   float speed, int hp, int attackPower):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{
	padInputX = 0;
	padInputY = 0;
	battery = 100;
	batteryTimer = 0;
	batteryChargeTimer = 0;
	shotBulletNum = 0;
	attackMotionFrame = 0;
}

Chara_Player::~Chara_Player()
{
	// �d�C�e
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// ����������
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	batteryTimer = 0;
	batteryChargeTimer = 0;
	shotBulletNum = 0;
}

// ���͂ł̈ړ�
void Chara_Player::InputMove()
{
	if ( isKnockBack )
	{
		return;
	}

	// ������
	moveX = 0.0f;
	moveY = 0.0f;

	// �p�b�h���o�[�̓��͏����擾
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// �_�b�V��
	if ( (InputManager::IsInputBarrage(e_MOVE_LEFT) ||
		  InputManager::IsInputBarrage(e_MOVE_RIGHT)) &&
		!InputManager::IsInputNow(e_FIXED_DIRECTION) )
	{
		speed = P_DASH_SPEED;
	}
	else if ( padInputX != 0 || padInputY != 0 )
	{
		speed = P_NORMAL_SPEED;
	}

	// �����Œ肪������Ă��邩�������ɐi�s����ꍇ��speed��x������
	if ( InputManager::IsInputNow(e_FIXED_DIRECTION) )
	{
		// ������
		if ( isLeftWard )
		{
			// ���i�s
			if ( padInputX < 0 )
			{
				speed = P_NORMAL_SPEED;
			}
			// �E�i�s
			else if ( padInputX > 0 )
			{
				speed = P_NORMAL_SPEED / 2.0f;
			}
		}
		// �E����
		else
		{
			// ���i�s
			if ( padInputX < 0 )
			{
				speed = P_NORMAL_SPEED / 2.0f;
			}
			// �E�i�s
			else if ( padInputX > 0 )
			{
				speed = P_NORMAL_SPEED;
			}
		}
	}

	// �����L�[/�A�i���O�X�e�B�b�N�ł̍��E�ړ�
	moveX += speed * (padInputX / 1000.0f);

	// �W�����v
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// �W�����v�̏�����
		CharaJump();
	}

	// �W�����v�㏸�����ɃL�[�������ꂽ�ꍇ�W�����v�𒆎~
	if ( isJump && gravity < JUMP_POWER / 2.0f )
	{
		if ( InputManager::IsInputNo(e_JUMP) )
		{
			gravity = JUMP_POWER / 1.5f;
			isJump = false;
		}
	}
}

// �ړ�
void Chara_Player::Move()
{
	InputMove();
	CharaMove((float)width / 2.0f, (float)height / 2.0f);

	// ��ʓ��ɂƂǂ܂�(X�����ɂ��Ă̂�)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// �摜�̌�����ύX
void Chara_Player::ChangeGraphicDirection()
{
	// ������
	if ( padInputX < 0 )
	{
		isLeftWard = true;
	}
	// �E����
	else if ( padInputX > 0 )
	{
		isLeftWard = false;
	}
}

// �o�b�e���[����
void Chara_Player::BatteryDecrease()
{
	// �ړ���
	if ( moveX != 0.0f || moveY != 0.0f || isJump || isFall )
	{
		batteryTimer++;
		if ( batteryTimer > BATTERY_DCREASE_TIME )
		{
			// �o�b�e���[����
			battery--;

			// �^�C�}�[���Z�b�g
			batteryTimer = 0;
		}

		batteryChargeTimer = 0;
	}

	// �������e������萔�𒴂���
	if ( shotBulletNum >= P_CONSUMPTION_BULLET_NUM )
	{
		// �o�b�e���[����
		battery -= 2;
		shotBulletNum = 0;
	}
}

// �o�b�e���[�`���[�W
void Chara_Player::BatteryCharge()
{
	if ( battery == P_MAX_BATTERY )
	{
		batteryChargeTimer = 0;
		return;
	}

	// �ړ����łȂ�
	if ( moveX == 0.0f && moveY == 0.0f && (!isJump || !isFall) )
	{
		const int charge = 60;
		// ��莞�ԃ`���[�W�Ń`���[�W�ʂ�����
		if ( batteryChargeTimer < charge * 3 )
		{
			batteryChargeTimer++;
		}
		else if ( batteryChargeTimer < charge * 6 )
		{
			batteryChargeTimer += 2;
		}
		else if ( batteryChargeTimer < charge * 9 )
		{
			batteryChargeTimer += 3;
		}
		else if ( batteryChargeTimer < charge * 12 )
		{
			batteryChargeTimer += 5;
		}
		else
		{
			batteryChargeTimer += 6;
		}

		// �o�b�e���[�㏸
		if ( batteryChargeTimer % BATTERY_CHARGE_TIME == 0 )
		{
			battery++;
		}

		// �`���[�W���̓o�b�e���[�͌������Ȃ�
		batteryTimer = 0;

		return;
	}
}

// �o�b�e���[�Ǘ�
void Chara_Player::BatteryManager()
{
	BatteryDecrease();
	BatteryCharge();

	// �o�b�e���[�͍ő�l�𒴂��Ȃ�
	if ( battery > P_MAX_BATTERY )
	{
		battery = 100;
	}

	// 0�ȉ��ɂ��Ȃ�Ȃ�
	if ( battery < 0 )
	{
		battery = 0;
	}
}

// �U�����[�V����
void Chara_Player::AttackMotion()
{
	if ( !isAttack )
	{
		return;
	}

	if ( attackMotionFrame++ > 30 )
	{
		attackMotionFrame = 0;
		isAttack = false;
	}
}

// ���
void Chara_Player::State()
{
	// �ҋ@
	if ( moveX == 0.0f && moveY == 0.0f )
	{
		state = e_P_STATE_IDLE;
	}
	else
	{
		// ����
		if ( fabsf(speed) == P_NORMAL_SPEED )
		{
			state = e_P_STATE_WALK;
		}
		// �_�b�V��
		else
		{
			state = e_P_STATE_DASH;
		}
	}

	// �[�d
	if ( batteryChargeTimer > BATTERY_CHARGE_TIME )
	{
		state = e_P_STATE_CHARGE;
	}

	// �W�����v
	if ( isJump || isFall )
	{
		state = e_P_STATE_JUMP;
	}

	// �U��
	if ( isAttack )
	{
		if ( moveX == 0.0f )
		{
			state = e_P_STATE_STOP_ATTACK;
		}
		else
		{
			// ����
			if ( fabsf(speed) == P_NORMAL_SPEED )
			{
				state = e_P_STATE_WALK_ATTACK;
			}
			// �_�b�V��
			else
			{
				state = e_P_STATE_DASH_ATTACK;
			}
		}

		// �W�����v
		if ( isJump || isFall )
		{
			state = e_P_STATE_JUMP_ATTACK;
		}
	}

	// �_���[���󂯂�(�F�_�Œ�)
	if ( isCBlinking )
	{
		state = e_P_STATE_RECIEVE_DAMAGE;
	}
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		BatteryManager();
		HpManager();
		AttackMotion();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		Invicible();
		State();

		// �����Œ�{�^����������Ă��Ȃ�
		if ( !InputManager::IsInputNow(e_FIXED_DIRECTION) )
		{
			ChangeGraphicDirection();
		}

		LocalAnimation(P_MOTION, P_NORMAL_SPEED);
	}

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Chara_Player::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	// �v���C���[
	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetPlayer(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �f�o�b�O�p
	DrawFormatString(0, 0, GetColor(255, 255, 255), "hp:%d%", hp);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "battery:%d%", battery);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "gravity:%f%", gravity);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "moveX:%f%", moveX);
	DrawFormatString(80, 160, GetColor(255, 255, 255), "r:%f", r);
	DrawFormatString(80, 180, GetColor(255, 255, 255), "g:%f", g);
	DrawFormatString(80, 200, GetColor(255, 255, 255), "b:%f", b);
	DrawFormatString(80, 240, GetColor(255, 255, 255), "h:%f", h);
	DrawFormatString(80, 260, GetColor(255, 255, 255), "s:%f", s);
	DrawFormatString(80, 280, GetColor(255, 255, 255), "v:%f", v);
	DrawFormatString(80, 300, GetColor(255, 255, 255), "invicibleTimer:%d", invicibleTimer);
	DrawFormatString(80, 320, GetColor(255, 255, 255), "blendMode:%d", blendMode);

	DrawFormatString((int)x - scrollX, (int)y - 40 - scrollY, GetColor(255, 255, 255), "x:%.2f,y+height:%.2f", x, y + height);
	//DrawFormatString((int)x - scrollX, (int)y - 40 - scrollY, GetColor(255, 255, 255), "attackMotionFrame:%d", attackMotionFrame);
}

// �U��
bool Chara_Player::IsAttack()
{
	// ���S���܂��͍U�����󂯂Ă���Ƃ��͍U���ł��Ȃ�
	if ( !isAlive || isCBlinking )
	{
		return false;
	}

	if ( InputManager::IsInputTrigger(e_ATTACK) )
	{
		// �������e���𑝂₷
		shotBulletNum++;
		batteryChargeTimer = 0;
		attackMotionFrame = 0;

		isAttack = true;

		return true;
	}

	return false;
}

// �U���q�b�g
void Chara_Player::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// �U�������̊Ǘ�
void Chara_Player::WeaponManager()
{
	// ����
	if ( IsAttack() && isAlive )
	{
		int xx = 16;
		if ( isLeftWard )
		{
			xx *= -1;
		}

		electricGun.push_back(new Weapon_ElectricGun(x + xx, y,
													 16,
													 EG_SPEED,
													 0.0f, 2,
													 isLeftWard));
	}

	// �d�C�e
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Update();
	}

	// �d�C�e�폜
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		if ( !electricGun[i]->GetIsAlive() )
		{
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}
	}
}

// �d�C�e�̗v�f��
unsigned int Chara_Player::GetGunSize()
{
	return electricGun.size();
}

// �d�C�e��X���W�擾
float Chara_Player::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// �d�C�e��Y���W�擾
float Chara_Player::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// �d�C�e��radius�擾
int Chara_Player::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}

// �d�C�e��isLeftWard�擾
bool Chara_Player::GetIsGunLeftWard(int index)
{
	return electricGun[index]->GetIsLeftWard();
}