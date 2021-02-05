#pragma once

#include "DxLib.h"

// �p�b�h�̃L�[�R���t�B�O
enum PadConfig
{
	e_PAD_MOVE_LEFT = PAD_INPUT_LEFT,	// ���ړ�
	e_PAD_MOVE_RIGHT = PAD_INPUT_RIGHT,	// �E�ړ�
	e_PAD_DASH = PAD_INPUT_6,			// �_�b�V��
	e_PAD_JUMP = PAD_INPUT_1,			// �W�����v
	e_PAD_ATTACK = PAD_INPUT_3,			// �U��
	e_PAD_LOCK = PAD_INPUT_5,			// �����Œ�
	e_PAD_HELP = PAD_INPUT_4,			// �w���v(������@��\��)
	e_PAD_START = PAD_INPUT_1,			// �Q�[���J�n
	e_PAD_EXIT = PAD_INPUT_8,			// �Q�[���I��
};

class InputPad
{
private:
	static int pad1;	// �p�b�h1�̓��͏��
	static int oldPad1;	// 1�t���[���O�̃p�b�h1�̓��͏��

	InputPad();

public:
	static int inputX;	// �p�b�h���o�[�̍��E�̓��͏����i�[
	static int inputY;	// �p�b�h���o�[�̏㉺�̓��͏����i�[

	// �X�V����
	static void Update();

	// ������Ă���ꍇTRUE
	static bool IsPadInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsPadInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsPadInputRelease(int key);

	// �A�ł��ꂽ�ꍇTRUE
	static bool IsPadInputBarrage(int key);

	// ������Ă��Ȃ��ꍇ
	static bool IsPadInputNot(int key);

	// pad��inputX���擾
	static int GetInputX();

	// pad��inputX���擾
	static int GetInputY();
};