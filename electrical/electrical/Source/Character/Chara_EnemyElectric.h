#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_ElectricGun.h"

enum EnemyElectricState
{
	e_EE_STATE_WALK,				// ����
	e_EE_STATE_JUMP,				// �W�����v
	e_EE_STATE_ATTACK,				// �U��
	e_EE_STATE_RECIEVE_DAMAGE,		// �_���[�W���󂯂�
	e_EE_STATE_NUM
};

extern const int EE_WIDTH;						// ����
extern const int EE_HEIGHT;						// �c��
extern const float EE_NORMAL_SPEED;				// �ʏ�X�s�[�h
extern const int EE_BULLET_INTERVAL ;			// �Ԋu
extern const int EE_MOTION[e_EE_STATE_NUM][4];	// ���[�V����

class Chara_EnemyElectric:public Chara_EnemyBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int shotBulletNum;		// �������e��
	int bulletInterval;		// �e�����Ԋu
	int shotLength;
	bool isTargetLock;		// �͈͓��̃t���O

	// �����ړ�
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// �ړ�
	void Move(float playerX, float playerY,
			  int screenX, int screenY, bool isPlayerAlive);

	// ���폈���Ǘ�
	void WeaponManager();

	// �U���Ǘ�
	void AttackManager(float playerX, float playerY, bool isPlayerAlive);

	// ���
	void State();

public:
	Chara_EnemyElectric(float x, float y, int radius, int width, int height,
						float speed, int hp, int attackPower, int mapChipX, int mapChipY);
	~Chara_EnemyElectric();

	// �X�V����
	void Update(float playerX, float playerY,
				int screenX, int screenY, bool isPlayerAlive) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	// �U���q�b�g
	void HitAttack() override;
};