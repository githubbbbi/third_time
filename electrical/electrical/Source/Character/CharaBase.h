#pragma once

#include "Animation.h"

extern const int CHARA_SIZE;		// �L�����N�^�̃T�C�Y
extern const float GRAVITY;			// �d��
extern const float JUMP_POWER;		// �W�����v��
extern const int INVICIBLE_TIME;	// ���G����

class CharaBase
{
private:
	Animation *anim;

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
	int hp;					// HP
	int attackPower;		// �U����
	bool isAlive;			// �����t���O
	bool isLeftWard;		// �������t���O
	bool isJump;			// �W�����v�t���O
	bool isFall;			// �����t���O
	bool isAttack;			// �U���t���O
	float r;				// �ԐF				:0~255
	float g;				// �ΐF				:0~255
	float b;				// �F				:0~255
	float h;				// �F��(hue)			:0~360
	float s;				// �ʓx(saturation)	:0~255
	float v;				// ���x(value)		:0~255

	int state;				// ���݂̏��(�ҋ@�A����Ȃ�)
	int graphIndex;			// �摜�Y����

	int cBlinkingTimer;		// �F�_�Ń^�C�}�[
	int cBlinkingCounter;	// �F�_�ŉ񐔃J�E���^�[
	bool isCBlinking;		// �F�_�Ńt���O

	int bBlinkingTimer;		// �u�����h�_�Ń^�C�}�[
	int bBlinkingCounter;	// �u�����h�_�ŉ񐔃J�E���^�[
	bool isBBlinking;		// �u�����h�_�Ńt���O

	bool isKnockBack;		// �m�b�N�o�b�N�t���O
	bool isAttackLeftWard;	// �U���̍������t���O

	int invicibleTimer;		// ���G����
	bool isInvicible;		// ���G�t���O

	int blendMode;			// �u�����h���[�h
	int blendValue;			// �u�����h�l

	// �L�����N�^�̏㏸&����
	void CharaRiseAndFall();

	// �L�����̈ړ�
	void CharaMove(float hitWidth, float hitHeight);

	// HP(�o�b�e���[)��0
	void HpZero();

	// HP�Ǘ�
	void HpManager();

	// �F�ɂ��Ďw�肳�ꂽ�񐔂����_��
	void ColorBlinking(float h, float s, float v, int change, int num);

	// Blend�ɂ��Ďw�肳�ꂽ�񐔂����_��
	void BlendBlinking(int blendMode1, int bledMode2,
					   int blendValue1, int blendValue2, int change, int num);

	// �m�b�N�o�b�N
	void KnockBack();

	// ���G�̏���
	void Invicible();

	// �A�j���[�V����
	void LocalAnimation(const int MOTION[][4],
						const float NORMAL_SPEED, const float DASH_SPEED);

public:
	// �R���X�g���N�^�錾
	CharaBase(float x, float y, int radius, int width, int height,
			  float speed, int hp, int attackPower);

	// �f�X�g���N�^
	~CharaBase();

	// �L�����N�^�̃W�����v
	void CharaJump();

	// �_���[�W���󂯂�
	void ReceiveDamage(int attackPower, bool isAttackLeftWard);

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

	// isInvicible���擾
	bool GetIsInvicible();
};