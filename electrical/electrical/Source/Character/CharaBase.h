#pragma once

// �ʏ�X�s�[�h
const float NORMAL_SPEED = 4.0f;

// �d��
const float GRAVITY = 0.8f;

// �W�����v��
const float JUMP_POWER = -13.0f;

class CharaBase
{
protected:
	float x;			// ���S���W
	float y;			// ���S���W
	float oldX;			// 1�t���[���O�̍��W
	float oldY;			// 1�t���[���O�̍��W
	float moveX;		// �ړ���
	float moveY;		// �ړ���
	float speed;		// �X�s�[�h
	float gravity;		// �����x
	int radius;			// ���a
	int graphHandle;	// �摜�n���h��
	int hp;				// HP
	int attackPower;	// �U����
	bool isAlive;		// �����t���O
	bool isLeftWard;	// �������t���O
	bool isJump;		// �W�����v�t���O
	bool isFall;		// �����t���O

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

	void CharaJump();

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// ���a���擾
	int GetRadius();

	// �U���͂��擾
	int GetAttackPower();

	// isAlive���擾
	bool GetIsAlive();

	// isLeftWard���擾
	bool GetIsLeftWard();

	// �_���[�W���󂯂�
	void ReceiveDamage(int attackPower);

	// �L�����N�^���m���ڐG
	void CharactersCollision();
};