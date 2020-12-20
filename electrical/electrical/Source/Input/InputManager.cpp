#include "InputManager.h"
#include "InputKey.h"
#include "InputPad.h"

// �ϐ�������
bool InputManager::isInputKey = false;
bool InputManager::isInputPad = false;

int InputManager::keyCode = 0;

// �L�[�R�[�h�ϊ�
void InputManager::ConversionKeyCode(int key)
{
	// �L�[�{�[�h
	if ( isInputKey )
	{
		if ( key == e_LEFT )
		{
			keyCode = e_KEY_LEFT;
		}
		else if ( key == e_RIGHT )
		{
			keyCode = e_KEY_RIGHT;
		}
		else if ( key == e_JUMP )
		{
			keyCode = e_KEY_JUMP;
		}
		else if ( key == e_ATTACK )
		{
			keyCode = e_KEY_ATTACK;
		}
		else if ( key == e_FIXED_DIRECTION )
		{
			keyCode = e_KEY_FIXED_DIRECTION;
		}
		else if ( key == e_EXIT )
		{
			keyCode = e_KEY_EXIT;
		}
	}

	// �p�b�h
	if ( isInputPad )
	{
		if ( key == e_LEFT )
		{
			keyCode = e_PAD_LEFT;
		}
		else if ( key == e_RIGHT )
		{
			keyCode = e_PAD_RIGHT;
		}
		else if ( key == e_JUMP )
		{
			keyCode = e_PAD_JUMP;
		}
		else if ( key == e_ATTACK )
		{
			keyCode = e_PAD_ATTACK;
		}
		else if ( key == e_FIXED_DIRECTION )
		{
			keyCode = e_PAD_FIXED_DIRECTION;
		}
		else if ( key == e_EXIT )
		{
			keyCode = e_PAD_EXIT;
		}
	}
}

// �X�V����
void InputManager::Update()
{
	// �L�[�{�[�h
	if ( CheckHitKeyAll() )
	{
		isInputKey = true;
		isInputPad = false;
	}

	// �p�b�h
	if ( GetJoypadInputState(DX_INPUT_PAD1) )
	{
		isInputPad = true;
		isInputKey = false;
	}

	InputKey::Update();
	InputPad::Update();
}

// ������Ă���ꍇTRUE
bool InputManager::IsInputNow(int key)
{
	ConversionKeyCode(key);

	// �L�[�{�[�h����
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputNow(keyCode) )
		{
			return true;
		}
	}

	// �p�b�h����
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputNow(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
bool InputManager::IsInputTrigger(int key)
{
	ConversionKeyCode(key);

	// �L�[�{�[�h����
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputTrigger(keyCode) )
		{
			return true;
		}
	}

	// �p�b�h����
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputTrigger(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// ������Ă��ė����ꂽ�u��TRUE
bool InputManager::IsInputRelease(int key)
{
	ConversionKeyCode(key);

	// �L�[�{�[�h����
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputRelease(keyCode) )
		{
			return true;
		}
	}

	// �p�b�h����
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputRelease(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// �A�ł��ꂽ�ꍇTRUE
bool InputManager::IsInputBarrage(int key)
{
	ConversionKeyCode(key);

	// �L�[�{�[�h����
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputBarrage(keyCode) )
		{
			return true;
		}
	}

	// �p�b�h����
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputBarrage(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// ������Ă��Ȃ��ꍇ
bool InputManager::IsInputNot(int key)
{
	ConversionKeyCode(key);

	// �L�[�{�[�h����
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputNot(keyCode) )
		{
			return true;
		}
	}

	// �p�b�h����
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputNot(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// pad��inputX���擾
int InputManager::GetPadInputX()
{
	return InputPad::GetInputX();
}

// pad��inputX���擾
int InputManager::GetPadInputY()
{
	return InputPad::GetInputY();
}