#pragma once

#include "DxLib.h"

// �L�[�{�[�h�̃L�[�R���t�B�O
enum KeyConfig
{
	e_KEY_MOVE_LEFT = KEY_INPUT_LEFT,	// ���ړ�
	e_KEY_MOVE_RIGHT = KEY_INPUT_RIGHT,	// �E�ړ�
	e_KEY_DASH = KEY_INPUT_LSHIFT,		// �_�b�V��
	e_KEY_JUMP = KEY_INPUT_UP,			// �W�����v
	e_KEY_ATTACK = KEY_INPUT_SPACE,		// �U��
	e_KEY_LOCK = KEY_INPUT_Z,			// �����Œ�
	e_KEY_HELP = KEY_INPUT_H,			// �w���v(������@��\��)
	e_KEY_START = KEY_INPUT_SPACE,		// �Q�[���J�n
	e_KEY_EXIT = KEY_INPUT_ESCAPE,		// �Q�[���I��
};

class InputKey
{
private:
	static char keys[256];		// �ŐV�̃L�[�{�[�h���
	static char oldKeys[256];	// 1�t���[���O�̃L�[�{�[�h���

	InputKey();

public:
	// �X�V����
	static void Update();

	// ������Ă���ꍇTRUE
	static bool IsKeyInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsKeyInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsKeyInputRelease(int key);

	// �A�ł��ꂽ�ꍇTRUE
	static bool IsKeyInputBarrage(int key);

	// ������Ă��Ȃ��ꍇ
	static bool IsKeyInputNot(int key);
};