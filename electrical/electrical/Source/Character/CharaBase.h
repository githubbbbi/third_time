#pragma once

// �d��
extern const float GRAVITY;

// �W�����v��
extern const float JUMP_POWER;

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
			  float speed, int hp, int graphHandle);

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// ���a���擾
	int GetRadius();

	//// ����������
	//virtual void Initialize() = 0;

	//// �X�V����
	//virtual void Update() = 0;

	//// �`�揈��
	//virtual void Draw() = 0;
};