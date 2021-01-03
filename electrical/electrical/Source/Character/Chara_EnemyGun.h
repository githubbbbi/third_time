#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

const int BULLET_INTERVAL = 70;

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// �������e��
	int bulletInterval;		// �e�����Ԋu
	bool isTargetLock;		// �͈͓��̃t���O

	// �ړ�
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyGun(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U�������Ǘ�
	void WeaponManager(int electricGunGH);

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