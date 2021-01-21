#pragma once

#include "Chara_EnemyBase.h"

enum EnemyBombState
{
	e_EB_STATE_WALK,				// ����
	e_EB_STATE_JUMP,				// �W�����v
	e_EB_STATE_ATTACK,				// �U��
	e_EB_STATE_RECIEVE_DAMAGE,		// �_���[�W���󂯂�
	e_EB_STATE_NUM
};

extern const int EB_WIDTH;						// ����
extern const int EB_HEIGHT;						// �c��
extern const float EB_NORMAL_SPEED;				// �ʏ�X�s�[�h
extern const float EB_DASH_SPEED;				// �_�b�V���X�s�[�h
extern const int EB_MOTION[e_EB_STATE_NUM][4];	// ���[�V����

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// �����ړ�
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// �ړ�
	void Move(float playerX, float playerY, bool isPlayerAlive);

	// �U���Ǘ�
	void AttackManager(bool isPlayerAlive);

	// ���
	void State();

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower);
	~Chara_EnemyBomb() = default;

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive) override;

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	// �U���q�b�g
	void HitAttack() override;
};