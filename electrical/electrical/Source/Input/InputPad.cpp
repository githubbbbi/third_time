#include "DxLib.h"
#include "InputPad.h"

// �ϐ�������
int InputPad::pad1 = 0;
int InputPad::oldPad1 = 0;

// �X�V����
void InputPad::Update()
{
	oldPad1 = pad1;
	pad1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

// ������Ă���ꍇTRUE
bool InputPad::IsPadInputNow(int key)
{
	if ( (pad1 & key) )
	{
		return true;
	}

	return false;
}

// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
bool InputPad::IsPadInputTrigger(int key)
{
	if ( !(oldPad1 & key) && (pad1 & key) )
	{
		return true;
	}

	return false;
}

// ������Ă��ė����ꂽ�u��TRUE
bool InputPad::IsPadInputRelease(int key)
{
	if ( (oldPad1 & key) && !(pad1 & key) )
	{
		return true;
	}

	return false;
}