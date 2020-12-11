#pragma once

// �d��
const float GRAVITY = 0.8f;

// �W�����v��
const float JUMP_POWER = -13.0f;

class CharaBase
{
protected:
	float x, y;			// ���S���W
	float moveX, moveY;	// �ړ���
	float speed;		// �X�s�[�h
	float gravity;		// �����x
	int radius;			// ���a
	int graphHandle;	// �摜�n���h��

	int hp;	// HP
	int attackPower;// �U����

	bool isAlive;		// �����t���O
	bool isLeftWard;	// �������t���O

	bool isJump;		// �W�����v�t���O

	// �L�����N�^�̗���
	void CharaFall();

	// �L�����̈ړ�
	void CharaMove();

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// HP(�o�b�e���[)��0
	void HpZero();

public:
	// �R���X�g���N�^�錾
	CharaBase(float x, float y, int radius,
			  float speed, int hp, int attackPower, int graphHandle);

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// ���a���擾
	int GetRadius();

	// �U���͂��擾
	int GetAttackPower();

	// isLeftWard���擾
	bool GetIsLeftWard();
};