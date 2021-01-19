#pragma once

#include "CharaBase.h"
#include "Animation.h"

enum EnemyState
{
	e_E_STATE_IDLE,					// �ҋ@
	e_E_STATE_WALK,					// ����
	e_E_STATE_JUMP,					// �W�����v
	e_E_STATE_ATTACK,				// �U��
	e_E_STATE_RECIEVE_DAMAGE,		// �_���[�W���󂯂�
	e_E_STATE_NUM
};

extern const int E_MOTION[e_E_STATE_NUM][4];	// �G�l�~�[�̃��[�V����

class Chara_EnemyBase:public CharaBase
{
private:
	Animation *anim;

protected:
	// �W�����v����
	void Jump();

	// �i�s������ς���
	void ChangeDirection();

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// �v���C���[�Ƃ̊ԂɃu���b�N�����邩�T��
	bool IsBlock(float playerX);

	// ���
	void State();

	// �A�j���[�V����
	void LocalAnimation();

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower);
};