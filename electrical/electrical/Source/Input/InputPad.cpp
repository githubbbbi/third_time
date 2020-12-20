#include "InputPad.h"

// �ϐ�������
int InputPad::pad1 = 0;
int InputPad::oldPad1 = 0;

int InputPad::inputX = 0;
int InputPad::inputY = 0;

// �X�V����
void InputPad::Update()
{
	oldPad1 = pad1;
	pad1 = GetJoypadInputState(DX_INPUT_PAD1);

	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_KEY_PAD1);
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

// 2��A�ł�TRUE
bool InputPad::IsPadInputBarrage(int key)
{
	// ���������Ԃ��v�����邽�߂̕ϐ�
	static int pushTime[2] = { 0 };

	// �O�̃t���[���𔻒肷�邽�߂̕ϐ�
	static int oldFrame[2] = { 0 };

	// �ĂуL�[���͂�����܂ő҂Ă�t���[����
	const int waitFrame = 15;

	// �X�e�B�b�N�������͂����Ƃ�
	if ( key == e_PAD_LEFT )
	{
		if ( !oldFrame[0] && (pad1 & key) )
		{
			// �������u�ԂȂ�
			if ( pushTime[0] != 0 )
			{
				return true;
			}
			else
			{
				pushTime[0] = waitFrame;
			}
		}

		oldFrame[0] = (pad1 & key);

		// ���������Ԃ�0����Ȃ��Ȃ�
		if ( pushTime[0] != 0 )
		{
			// ���������Ԃ��f�N�������g
			pushTime[0]--;
		}
	}
	// �X�e�B�b�N���E���͂����Ƃ�
	else if ( key == e_PAD_RIGHT )
	{
		if ( !oldFrame[1] && (pad1 & key) )
		{
			// �������u�ԂȂ�
			if ( pushTime[1] != 0 )
			{
				return true;
			}
			else
			{
				pushTime[1] = waitFrame;
			}
		}

		oldFrame[1] = (pad1 & key);

		// ���������Ԃ�0����Ȃ��ꍇ
		if ( pushTime[1] != 0 )
		{
			// ���������Ԃ��f�N�������g
			pushTime[1]--;
		}
	}

	return false;
}

// ������Ă��Ȃ��ꍇ
bool InputPad::IsPadInputNot(int key)
{
	if ( !(pad1 & key) )
	{
		return true;
	}

	return false;
}

// pad��inputX���擾
int InputPad::GetInputX()
{
	return inputX;
}

// pad��inputY���擾
int InputPad::GetInputY()
{
	return inputY;
}