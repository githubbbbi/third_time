#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

extern const int E_WATER_WIDTH;		// ����
extern const int E_WATER_HEIGHT;	// �c��

extern const int BULLET_INTERVAL;

class Chara_EnemyWater:public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// �e�����Ԋu
	float bulletSpeed;		// �e�̃X�s�[�h

	// �ړ�
	void Move();

	// ������ύX
	void ChangeDirection(float playerX);

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower);
	~Chara_EnemyWater();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U���q�b�g
	void HitAttack(int index);

	// ���폈���Ǘ�
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive);

	// ���e�̗v�f��
	unsigned int GetGunSize();

	// ���e��X���W�擾
	float GetGunPosX(int index);

	// ���e��Y���W�擾
	float GetGunPosY(int index);

	// ���e��radius�擾
	int GetGunRadius(int index);

	// ���e��isLeftWard�擾
	bool GetIsGunLeftWard(int index);
};