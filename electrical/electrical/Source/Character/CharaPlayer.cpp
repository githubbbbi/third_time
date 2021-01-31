#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"
#include "../Resource/Sound_SE.h"

const int P_WIDTH = 30;
const int P_HEIGHT = 50;
const float P_NORMAL_SPEED = 3.0f;
const float P_DASH_SPEED = 5.0f;
const float P_JUMP_POWER = -15.0f;
const int BATTERY_DCREASE_TIME = 60 * 1;
const int BATTERY_CHARGE_TIME = 60 * 1;
const int P_MAX_HP = 100;
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
	{ 36, 37, 38, 39 },
	{ 40, 41, 42, 43 },
	{ 44, 45, 46, 47 }
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
	isBatteryZero = false;

	batteryBox = { 0.0f, 0.0f, 0.0f, 0.0f,
				   255.0f, 255.0f, 255.0f,
				   215.0f, 230.0f, 200.0f };
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

// �����̉摜�̌���
bool Chara_Player::InitGraphDirection()
{
	// ���[���h���W�����[�J�����W�֕ϊ�
	// ���[���h���W���E�B���h�E�T�C�Y�ł��A�����遨�ǂ��̕����ɂ��邩�����܂�
	int localX = (int)x;
	int winX = ((int)x / WIN_WIDTH) * WIN_WIDTH;
	if ( winX > 0 )
	{
		localX = (int)x - winX + WIN_WIDTH / 2;
	}

	// �������W(�X�|�[���ʒu)�������
	if ( localX < WIN_WIDTH / 2 )
	{
		// �E������
		return false;
	}

	// �������W(�X�|�[���ʒu)���E���
	if ( localX > WIN_WIDTH / 2 )
	{
		// ��������
		return true;
	}

	return false;
}

// ����������
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;
	gravity = 0.0f;
	hp = P_MAX_HP;
	battery = P_MAX_BATTERY;
	batteryTimer = 0;
	batteryChargeTimer = 0;
	shotBulletNum = 0;
	attackMotionFrame = 0;

	// �摜�̌����̏�����
	isLeftWard = InitGraphDirection();

	// �o�b�e���[�{�b�N�X
	InitializeBatteryBox();

	MyInitialize();
}

// �ړ����͂����邩�̔���
bool Chara_Player::IsInputMove()
{
	return (padInputX != 0 || padInputY != 0);
}

// �_�b�V���̔���
bool Chara_Player::IsDash()
{
	return (InputManager::IsInputNow(e_DASH) ||
			InputManager::IsInputBarrage(e_MOVE_LEFT) ||
			InputManager::IsInputBarrage(e_MOVE_RIGHT)) &&
		!InputManager::IsInputNow(e_FIXED);
}

// �_�b�V���Ȃǂ̔��肩��X�s�[�h���擾
float Chara_Player::GetNowSpeed()
{
	// �_�b�V��
	if ( IsDash() )
	{
		return P_DASH_SPEED;
	}

	// �ʏ�ړ�
	if ( IsInputMove() )
	{
		return P_NORMAL_SPEED;
	}

	return 0.0f;
}

// �����Œ莞�̏���
void Chara_Player::Fixed()
{
	// �����Œ肪������Ă��邩�������ɐi�s����ꍇ��speed��x������
	if ( InputManager::IsInputNow(e_FIXED) )
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
}

// ���͂ł̈ړ�
void Chara_Player::InputMove()
{
	// �m�b�N�o�b�N���͓����Ȃ�
	if ( isKnockBack )
	{
		return;
	}

	// �o�b�e���[���[���̎��͓����Ȃ�
	if ( isBatteryZero )
	{
		moveX = 0.0f;
		moveY = 0.0f;

		return;
	}

	// �S�[��������͓����Ȃ�
	if ( IsGoal() )
	{
		moveX = 0.0f;
		moveY = 0.0f;

		return;
	}

	// ������
	moveX = 0.0f;
	moveY = 0.0f;

	// �p�b�h���o�[�̓��͏����擾
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// �X�s�[�h
	speed = GetNowSpeed();

	// �����Œ莞
	Fixed();

	// �����L�[/�A�i���O�X�e�B�b�N�ł̍��E�ړ�
	moveX += speed * (padInputX / 1000.0f);

	// �W�����v
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// �W�����v���ł��Ȃ��ꍇ�͏������s��Ȃ�
		if ( isJump || isFall )
		{
			return;
		}

		// SE�Đ�
		Sound_SE::GetInstance()->PlaySE(e_PLAYER_JUMP_SE, false);

		// �W�����v�̏�����
		CharaJump(P_JUMP_POWER);
	}

	// �W�����v�㏸�����ɃL�[�������ꂽ�ꍇ�W�����v�𒆎~
	if ( isJump && gravity < P_JUMP_POWER / 2.0f )
	{
		if ( InputManager::IsInputNot(e_JUMP) )
		{
			gravity = P_JUMP_POWER / 1.5f;
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
	// �S�[��������͏������s��Ȃ�
	if ( IsGoal() )
	{
		return;
	}

	// �_���[�W���󂯂Ă���Ƃ��͏������s��Ȃ�
	if ( isCBlinking )
	{
		batteryTimer = 0;
		return;
	}

	// �ړ���
	if ( moveX != 0.0f || moveY != 0.0f || isJump || isFall )
	{
		// ����
		if ( fabsf(speed) == P_NORMAL_SPEED )
		{
			batteryTimer++;
		}
		// �_�b�V��
		else
		{
			batteryTimer += 3;
		}

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
		battery -= 5;
		shotBulletNum = 0;
	}
}

// �o�b�e���`���[�W���s��Ȃ��ꍇ
void Chara_Player::NotBatteryChage()
{
	// SE��~
	Sound_SE::GetInstance()->StopSE(e_PLAYER_CHAGING_SE);
	batteryChargeTimer = 0;
}

// �o�b�e���[�`���[�W
void Chara_Player::BatteryCharge()
{
	// �S�[��������͏������s��Ȃ�
	if ( IsGoal() )
	{
		return;
	}

	// �o�b�e���[�����������o�b�e���[���ő�ɂȂ����Ƃ�
	if ( batteryChargeTimer > 0 && battery == P_MAX_BATTERY )
	{
		NotBatteryChage();
		return;
	}

	// �o�b�e���[���ő�ɂȂ����Ƃ��͏������s��Ȃ�
	if ( battery == P_MAX_BATTERY )
	{
		NotBatteryChage();
		return;
	}

	// �_���[�W���󂯂��Ƃ��͏������s��Ȃ�
	if ( isCBlinking )
	{
		NotBatteryChage();
		return;
	}

	// �ړ����͏������s��Ȃ�
	if ( moveX != 0.0f || moveY != 0.0f ||
		isJump || isFall )
	{
		NotBatteryChage();
		return;
	}

	// �U�����͏������s��Ȃ�
	if ( isAttack )
	{
		NotBatteryChage();
		return;
	}

	// ��������`���[�W����
	// SE�Đ�
	Sound_SE::GetInstance()->PlaySE(e_PLAYER_CHAGING_SE, true);
	batteryChargeTimer += 15;

	// �o�b�e���[�㏸
	if ( batteryChargeTimer % BATTERY_CHARGE_TIME == 0 )
	{
		battery++;
	}

	// �`���[�W���̓o�b�e���[�͌������Ȃ�
	batteryTimer = 0;

	return;
}

// �o�b�e���[�[��
void Chara_Player::BatteryZero()
{
	if ( !isBatteryZero )
	{
		return;
	}

	// ��x�o�b�e���[���[���ɂȂ��
	// �o�b�e���[���ő�ɂȂ�܂Ń[���t���O�͉�������Ȃ�
	if ( battery == P_MAX_BATTERY )
	{
		isBatteryZero = false;
	}
}

// �o�b�e���[�Ǘ�
void Chara_Player::BatteryManager()
{
	BatteryDecrease();
	BatteryCharge();
	BatteryZero();

	// �o�b�e���[�͍ő�l�𒴂��Ȃ�
	if ( battery > P_MAX_BATTERY )
	{
		battery = 100;
	}

	// 0�ȉ��ɂ��Ȃ�Ȃ�
	if ( battery < 0 )
	{
		battery = 0;
		isBatteryZero = true;
	}
}

// �U��
bool Chara_Player::IsAttack()
{
	// ���S���܂��͍U�����󂯂Ă���Ƃ��܂��̓o�b�e���[�[���̎��͍U���ł��Ȃ�
	if ( !isAlive || isCBlinking || isBatteryZero )
	{
		return false;
	}

	// �S�[�����͍U���ł��Ȃ�
	if ( IsGoal() )
	{
		return false;
	}

	if ( InputManager::IsInputTrigger(e_ATTACK) )
	{
		// �������e���𑝂₷
		shotBulletNum++;
		attackMotionFrame = 0;

		// �[�d���Ȃ�
		batteryChargeTimer = 0;

		isAttack = true;

		return true;
	}

	return false;
}

// �U�������̊Ǘ�
void Chara_Player::WeaponManager()
{
	// ����
	if ( IsAttack() && isAlive )
	{
		// �������W
		float xx = 24.0f;
		if ( isLeftWard )
		{
			xx *= -1.0f;
		}

		// �򋗗� �o�b�e���[�̎c�ʊ����ɂ���ĕω�
		auto BatteryRate = [this](int value)->bool
		{
			return ((float)battery / (float)P_MAX_BATTERY) * 100.f > value;
		};
		// 100%
		float flightDistance = 300.0f;
		// 80%
		if ( BatteryRate(80) )
		{
			flightDistance = 200.0f;
		}
		// 50%
		else if ( BatteryRate(50) )
		{
			flightDistance = 100.0f;
		}
		// 20%
		else if ( BatteryRate(20) )
		{
			flightDistance = 50.0f;
		}// 10%
		else if ( BatteryRate(10) )
		{
			flightDistance = 10.0f;
		}
		else
		{
			flightDistance = 5.0f;
		}

		electricGun.push_back(new Weapon_ElectricGun(x + xx, y,
													 16,
													 EG_SPEED, 0.0f,
													 flightDistance, 2,
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

// �S�[���ɓ����Ă��邩�̔���
bool Chara_Player::IsGoal()
{
	float dummy = 0.0f;
	const int hitHalfWidth = P_WIDTH / 2;
	const int hitHalfHeight = P_HEIGHT / 2;

	// �ꂩ���ł��܂܂�Ă��Ȃ���return
	// ����
	if ( Utility::MapHitCheck(x - hitHalfWidth, y + hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// �E��
	if ( Utility::MapHitCheck(x + hitHalfWidth, y + hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// ����
	if ( Utility::MapHitCheck(x - hitHalfWidth, y - hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// �E��
	if ( Utility::MapHitCheck(x + hitHalfWidth, y - hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	return true;
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

	// �o�b�e���[�[��
	if ( isBatteryZero )
	{
		state = e_P_STATE_BATTERY_ZERO;
	}

	// �_���[���󂯂�(�F�_�Œ�)
	if ( isCBlinking )
	{
		state = e_P_STATE_RECIEVE_DAMAGE;
	}

	// �S�[��
	if ( IsGoal() )
	{
		state = e_P_STATE_GOAL;
	}
}

// �o�b�e���[�{�b�N�X�̏���������
void Chara_Player::InitializeBatteryBox()
{
	// ������
	if ( isLeftWard )
	{
		batteryBox.boxPosLeft = x + 1.0f;
	}
	// �E����
	else
	{
		batteryBox.boxPosLeft = x - 19.0f;
	}

	batteryBox.boxPosRight = batteryBox.boxPosLeft + 18.0f;
	batteryBox.boxPosTop = y + 18.0f - 30.0f * ((float)battery / (float)P_MAX_BATTERY);
	batteryBox.boxPosBottom = y + 18.0f;

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&batteryBox.r, &batteryBox.g, &batteryBox.b,
							 batteryBox.h, batteryBox.s, batteryBox.v);
}

// �o�b�e���[�{�b�N�X�̍X�V����
void Chara_Player::UpdateBatteryBox()
{
	// ������
	if ( isLeftWard )
	{
		batteryBox.boxPosLeft = x + 1.0f;
	}
	// �E����
	else
	{
		batteryBox.boxPosLeft = x - 19.0f;
	}

	batteryBox.boxPosRight = batteryBox.boxPosLeft + 18.0f;
	batteryBox.boxPosTop = y + 18.0f - 30.0f * ((float)battery / (float)P_MAX_BATTERY);
	batteryBox.boxPosBottom = y + 18.0f;

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&batteryBox.r, &batteryBox.g, &batteryBox.b,
							 batteryBox.h, batteryBox.s, batteryBox.v);
}

// �o�b�e���[�{�b�N�X�̕`�揈��
void Chara_Player::DrawBatteryBox(float shakeX, float shakeY, int scrollX, int scrollY)
{
	DrawBox((int)(batteryBox.boxPosLeft + shakeX) - scrollX,
			(int)(batteryBox.boxPosTop + shakeY) - scrollY,
			(int)(batteryBox.boxPosRight + shakeX) - scrollX,
			(int)(batteryBox.boxPosBottom + shakeY) - scrollY,
			GetColor((int)batteryBox.r, (int)batteryBox.g, (int)batteryBox.b), true);
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

		// �o�b�e���[�{�b�N�X
		UpdateBatteryBox();

		// �����Œ�{�^����������Ă��Ȃ�
		if ( !InputManager::IsInputNow(e_FIXED) )
		{
			ChangeGraphicDirection();
		}

		Animation(P_MOTION, P_NORMAL_SPEED, P_DASH_SPEED);
	}

	WeaponManager();

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

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);

		// �o�b�e���[�{�b�N�X
		DrawBatteryBox(shakeX, shakeY, scrollX, scrollY);

		// �v���C���[
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetPlayer(graphIndex), true, isLeftWard);

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// �U���q�b�g
void Chara_Player::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// �X�|�[��
void Chara_Player::Spawn(float x, float y)
{
	this->x = x;
	this->y = y;
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

// HP���擾
int Chara_Player::GetHp()
{
	return hp;
}

// �o�b�e���[���擾
int Chara_Player::GetBattery()
{
	return battery;
}

// �S�[��������擾
bool Chara_Player::GetIsGoal()
{
	return IsGoal();
}