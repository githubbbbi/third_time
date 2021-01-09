#pragma once

const float GRAVITY = 0.8f;			// �d��
const float JUMP_POWER = -13.0f;	// �W�����v��

class CharaBase
{
protected:
	float x;				// ���S���W
	float y;				// ���S���W
	float oldX;				// 1�t���[���O�̍��W
	float oldY;				// 1�t���[���O�̍��W
	float moveX;			// �ړ���
	float moveY;			// �ړ���
	float speed;			// �X�s�[�h
	float gravity;			// �����x
	int radius;				// ���a
	int width;				// ����
	int height;				// �c��
	int graphHandle;		// �摜�n���h��
	int hp;					// HP
	int attackPower;		// �U����
	bool isAlive;			// �����t���O
	bool isLeftWard;		// �������t���O
	bool isJump;			// �W�����v�t���O
	bool isFall;			// �����t���O
	float r;				// �ԐF				:0~255
	float g;				// �ΐF				:0~255
	float b;				// �F				:0~255
	float h;				// �F��(hue)			:0~360
	float s;				// �ʓx(saturation)	:0~255
	float v;				// ���x(value)		:0~255
	
	int cBlinkingTimer;		// �F�_�Ń^�C�}�[
	int cBlinkingCounter;	// �F�_�ŉ񐔃J�E���^�[
	bool isCBlinking;		// �F�_�Ńt���O

	// �L�����N�^�̗���
	void CharaFall();

	// �L�����̈ړ�
	void CharaMove(float hitWidth, float hitHeight);

	// HP(�o�b�e���[)��0
	void HpZero();

	// HP�Ǘ�
	void HpManager();

	// �F�ɂ��Ďw�肳�ꂽ�񐔂����_��
	void ColorBlinking(float h, float s, float v, int noOfTimes);

public:
	// �R���X�g���N�^�錾
	CharaBase(float x, float y, int radius, int width, int height,
			  float speed, int hp, int attackPower, int graphHandle);

	void CharaJump();

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// oldX���W���擾
	float GetPosOldX();

	// oldY���W���擾
	float GetPosOldY();

	// �X�s�[�h���擾
	float GetSpeed();

	// ���a���擾
	int GetRadius();

	// width���擾
	int GetWidth();

	// height���擾
	int GetHeight();

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