#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

enum EnemyWaterState
{
	e_EW_STATE_IDLE,				// �ҋ@
	e_EW_STATE_ATTACK,				// �U��
	e_EW_STATE_RECIEVE_DAMAGE,		// �_���[�W���󂯂�
	e_EW_STATE_NUM
};

extern const int EW_WIDTH;						// ����
extern const int EW_HEIGHT;						// �c��
extern const int EW_BULLET_INTERVAL;			// �Ԋu
extern const int EW_MOTION[e_EW_STATE_NUM][4];	// ���[�V����

class Chara_EnemyWater:public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// �e�����Ԋu
	float bulletSpeed;		// �e�̃X�s�[�h

	int gunIndex;			// �e�̃C���f�b�N�X

	// �ړ�
	void Move();

	// ���폈���Ǘ�
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive);

	// �U���Ǘ�
	void AttackManager(float playerX, float playerY, bool isPlayerAlive);

	// ������ύX
	void ChangeDirection(float playerX);

	// ���
	void State();

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower);
	~Chara_EnemyWater();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	void HitAttack() override;
};