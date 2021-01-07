#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/ElectricGun.h"

const int BATTERY_DCREASE_TIME = 60 * 1;			// �o�b�e���[�����^�C��
const int BATTERY_CHARGE_TIME = (60 * 1) / 2;		// �o�b�e���[�`���[�W�^�C��
const int PLAYER_MAX_BATTERY = 100;					// �ő�o�b�e���[
const int PLAYER_CONSUMPTION_BULLET_NUM = 5;		// �d�͂������e��

class Chara_Player:public CharaBase
{
private:
	std::vector<ElectricGun *> electricGun;

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
	Chara_Player(float x, float y, int radius,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// ����������
	void Initialize();

	// �U�������Ǘ�
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