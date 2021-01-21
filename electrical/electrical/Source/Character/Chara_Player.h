#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/Weapon_ElectricGun.h"

enum PlayerState
{
	e_P_STATE_IDLE,					// �ҋ@
	e_P_STATE_CHARGE,				// �[�d
	e_P_STATE_WALK,					// ����
	e_P_STATE_DASH,					// �_�b�V��
	e_P_STATE_JUMP,					// �W�����v
	e_P_STATE_STOP_ATTACK,			// �Ƃ܂��čU��
	e_P_STATE_WALK_ATTACK,			// �����U��
	e_P_STATE_DASH_ATTACK,			// �_�b�V���U��
	e_P_STATE_JUMP_ATTACK,			// �W�����v�U��
	e_P_STATE_RECIEVE_DAMAGE,		// �_���[�W���󂯂�
	e_P_STATE_NUM
};

extern const int P_WIDTH;						// ����
extern const int P_HEIGHT;						// �c��
extern const float P_NORMAL_SPEED;				// �ʏ�X�s�[�h
extern const float P_DASH_SPEED;				// �_�b�V���X�s�[�h
extern const int BATTERY_DCREASE_TIME;			// �o�b�e���[�����^�C��
extern const int BATTERY_CHARGE_TIME;			// �o�b�e���[�`���[�W�^�C��
extern const int P_MAX_BATTERY;					// �ő�o�b�e���[
extern const int P_CONSUMPTION_BULLET_NUM;		// �d�͂������e��
extern const int P_MOTION[e_P_STATE_NUM][4];	// ���[�V����

const int P_MAX_HP = 100;						// �ő�HP

class Chara_Player:public CharaBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int padInputX, padInputY;	// �p�b�h���o�[�̓��͗�(�L�[�{�[�h�̖��L�[�̓��͗ʂ��擾�ł���)
	int battery;				// �o�b�e���[
	int batteryTimer;			// �o�b�e���[�����^�C�}�[
	int batteryChargeTimer;		// �o�b�e���[�`���[�W�^�C�}�[
	int shotBulletNum;			// �������e��

	int attackMotionFrame;		// �U�����[�V�����t���[��

	int uiHandle;				// UI�̃O���t�B�b�N��ۑ�

	// ���͂ł̈ړ�
	void InputMove();

	// �ړ�
	void Move();

	// �摜�̌�����ύX
	void ChangeGraphicDirection();

	// �o�b�e���[����
	void BatteryDecrease();

	// �o�b�e���[�`���[�W
	void BatteryCharge();

	// �o�b�e���[�[��
	bool BatteryZero();

	// �o�b�e���[�Ǘ�
	void BatteryManager();

	// �U��
	bool IsAttack();

	// ���폈���Ǘ�
	void WeaponManager();

	// �U�����[�V����
	void AttackMotion();

	// ���
	void State();

public:
	Chara_Player(float x, float y, int radius, int width, int height,
				 float speed, int hp, int attackPower);
	~Chara_Player();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U���q�b�g
	void HitAttack(int index);

	// �d�C�e�̗v�f��
	unsigned int GetGunSize();

	// �d�C�e��X���W���擾
	float GetGunPosX(int index);

	// �d�C�e��Y���W���擾
	float GetGunPosY(int index);

	// �d�C�e��radius���擾
	int GetGunRadius(int index);

	// �d�C�e��isLeftWard���擾
	bool GetIsGunLeftWard(int index);
};