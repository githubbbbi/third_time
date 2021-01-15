#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/Weapon_ElectricGun.h"

extern const int P_WIDTH;							// ����
extern const int P_HEIGHT;						// �c��
extern const float P_NORMAL_SPEED;				// �ʏ�X�s�[�h
extern const float P_DASH_SPEED;				// �_�b�V���X�s�[�h
extern const int BATTERY_DCREASE_TIME;		// �o�b�e���[�����^�C��
extern const int BATTERY_CHARGE_TIME;	// �o�b�e���[�`���[�W�^�C��
extern const int P_MAX_BATTERY;					// �ő�o�b�e���[
extern const int P_CONSUMPTION_BULLET_NUM;			// �d�͂������e��

class Chara_Player:public CharaBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int padInputX, padInputY;	// �p�b�h���o�[�̓��͗�(�L�[�{�[�h�̖��L�[�̓��͗ʂ��擾�ł���)
	int battery;				// �o�b�e���[
	int batteryTimer;			// �o�b�e���[�����^�C�}�[
	int batteryChargeTimer;		// �o�b�e���[�`���[�W�^�C�}�[
	int shotBulletNum;			// �������e��

	// �A�j���[�V����
	void Animation();

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

	// �o�b�e���[�Ǘ�
	void BatteryManager();

public:
	Chara_Player(float x, float y, int radius, int width, int height,
				 float speed, int hp, int attackPower);
	~Chara_Player();

	// ����������
	void Initialize();

	// ���폈���Ǘ�
	void WeaponManager();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U��
	bool IsAttack();

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