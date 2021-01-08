#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

const int E_GUN_WIDTH = 50;				// ����
const int E_GUN_HEIGHT = 50;			// �c��
const float E_GUN_NORMAL_SPEED = 2.0f;	// �ʏ�X�s�[�h
const float E_GUN_DASH_SPEED = 4.0f;	// �_�b�V���X�s�[�h

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
	Chara_EnemyGun(float x, float y, int radius, int width, int height,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// ���폈���Ǘ�
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