#pragma once

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;// HP�����^�C��
const int HP_CHARGE_TIME = (60 * 1) / 2;// HP�`���[�W�^�C��

const int MAX_HP = 100;

// �L�[�{�[�h�̃L�[�R���t�B�O
enum KeyConfig
{
	e_KEY_LEFT = KEY_INPUT_LEFT,	// ���ړ�
	e_KEY_RIGHT = KEY_INPUT_RIGHT,	// �E�ړ�
	e_KEY_JUMP = KEY_INPUT_UP,		// �W�����v
	e_KEY_ATTACK = KEY_INPUT_SPACE,	// �U��
};

// �p�b�h�̃L�[�R���t�B�O
enum PadConfig
{
	e_PAD_LEFT = PAD_INPUT_LEFT,	// ���ړ�
	e_PAD_RIGHT = PAD_INPUT_RIGHT,	// �E�ړ�
	e_PAD_JUMP = PAD_INPUT_1,		// �W�����v
	e_PAD_ATTACK = PAD_INPUT_3,		// �U��
};

class Chara_Player:public CharaBase
{
private:
	int hpTimer;// HP(�o�b�e���[)�^�C�}�[
	int chargeTimer;// HP(�o�b�e���[)�`���[�W�^�C�}�[

	// �ړ�
	void Move();

	// HP(�o�b�e���[)����
	void HpDcrease();

	// HP(�o�b�e���[)�`���[�W
	bool HpCharge();

public:
	Chara_Player(int x, int y, int radius,
				 int speed, int hp, int graphHandle);
	~Chara_Player();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};