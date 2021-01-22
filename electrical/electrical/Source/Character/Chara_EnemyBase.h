#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	int mapChipX;			// �}�b�v�`�b�v��X���W
	int mapChipY;			// �}�b�v�`�b�v��Y���W
	float attackX;			// �U�����S���W
	float attackY;			// �U�����S���W
	int attackRadius;		// �U�����a
	bool isAttackLeftWard;	// �U���������t���O

	// �W�����v����
	void Jump();

	// �i�s������ς���
	void ChangeDirection();

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// �v���C���[�Ƃ̊ԂɃu���b�N�����邩�T��
	bool IsBlock(float playerX);

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int mapChipX, int mapChipY);

	virtual void Update(float playerX, float playerY, bool isPlayerAlive) = 0;
	virtual void Draw(float shakeX, float shakeY, int scrollX, int scrollY) = 0;

	virtual void HitAttack() = 0;

	int GetMapChipX();
	int GetMapChipY();
	float GetAttackPosX();
	float GetAttackPosY();
	int GetAttackRadius();
	bool GetIsAttackLeftWard();
};