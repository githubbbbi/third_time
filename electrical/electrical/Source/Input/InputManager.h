#pragma once

enum
{
	e_MOVE_LEFT,		// ���ړ�
	e_MOVE_RIGHT,		// �E�ړ�
	e_JUMP,				// �W�����v
	e_ATTACK,			// �U��
	e_FIXED_DIRECTION,	// �����Œ�
	e_EXIT,				// �Q�[���I��
};

class InputManager
{
private:
	static bool isInputKey;	// �L�[���̓t���O
	static bool isInputPad;	// �p�b�h���̓t���O

	static int keyCode;// �L�[�R�[�h

	InputManager();

	// �L�[�R�[�h�ϊ�
	static void ConversionKeyCode(int key);

public:
	// �X�V����
	static void Update();

	// ������Ă���ꍇTRUE
	static bool IsInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsInputRelease(int key);

	// �A�ł��ꂽ�ꍇTRUE
	static bool IsInputBarrage(int key);

	// ������Ă��Ȃ��ꍇ
	static bool IsInputNot(int key);

	// pad��inputX���擾
	static int GetPadInputX();
	
	// pad��inputX���擾
	static int GetPadInputY();
};