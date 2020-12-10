#pragma once

// �p�b�h�̃L�[�R���t�B�O
enum PadConfig
{
	e_PAD_LEFT = PAD_INPUT_LEFT,	// ���ړ�
	e_PAD_RIGHT = PAD_INPUT_RIGHT,	// �E�ړ�
	e_PAD_JUMP = PAD_INPUT_1,		// �W�����v
	e_PAD_ATTACK = PAD_INPUT_3,		// �U��
};

class InputPad
{
private:
	static int pad1;	// �p�b�h1�̓��͏��
	static int oldPad1;	// 1�t���[���O�̃p�b�h1�̓��͏��

	InputPad();

public:
	// �X�V����
	static void Update();

	// ������Ă���ꍇTRUE
	static bool IsPadInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsPadInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsPadInputRelease(int key);
};