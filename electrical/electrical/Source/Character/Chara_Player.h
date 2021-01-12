#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/Weapon_ElectricGun.h"

const int P_WIDTH = 50;							// ����
const int P_HEIGHT = 50;						// �c��
const float P_NORMAL_SPEED = 3.0f;				// �ʏ�X�s�[�h
const float P_DASH_SPEED = 5.0f;				// �_�b�V���X�s�[�h
const int BATTERY_DCREASE_TIME = 60 * 1;		// �o�b�e���[�����^�C��
const int BATTERY_CHARGE_TIME = (60 * 1) / 2;	// �o�b�e���[�`���[�W�^�C��
const int P_MAX_BATTERY = 100;					// �ő�o�b�e���[
const int P_CONSUMPTION_BULLET_NUM = 5;			// �d�͂������e��

class Chara_Player:public CharaBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int padInputX, padInputY;	// �p�b�h���o�[�̓��͗�(�L�[�{�[�h�̖��L�[�̓��͗ʂ��擾�ł���)
	int battery;				// �o�b�e���[
	int batteryTimer;			// �o�b�e���[�����^�C�}�[
	int batteryChargeTimer;		// �o�b�e���[�`���[�W�^�C�}�[
	int shotBulletNum;			// �������e��

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
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// ����������
	void Initialize();

	// ���폈���Ǘ�
	void WeaponManager(int electricGunGH);

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

	// �d�C�e��X���W�擾
	float GetGunPosX(int index);

	// �d�C�e��Y���W�擾
	float GetGunPosY(int index);

	// �d�C�e��radius�擾
	int GetGunRadius(int index);
};