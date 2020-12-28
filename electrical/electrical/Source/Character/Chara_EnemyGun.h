#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// �������e��
	int bulletInterval;
	int targetlock;	//�͈͓��̃t���O
	
	// �ړ�
	void Move(float playerX, float playerY);

public:
	Chara_EnemyGun(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ����������
	void Initialize() override;

	// �X�V����
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY) override;

	// �U�������Ǘ�
	void WeaponManager(int electricGunGH) override;

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