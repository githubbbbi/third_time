#include "DxLib.h"
#include "InputPad.h"
#include "InputKey.h"

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

bool InputPad::IsPadInputBarrage(int key)
{
	//���������Ԃ��v�����邽�߂̕ϐ�
	static int pushTime[2] = { 0 };
	//�O�̃t���[���𔻒肷�邽�߂̕ϐ�
	static int oldFrame[2] = { 0 };
	//�ĂуL�[���͂�����܂ő҂Ă�t���[����
	const int waitFrame = 15;

	// �X�e�B�b�N�������͂����Ƃ�
	if (key == e_PAD_LEFT)
	{
		if (!oldFrame[0] && (pad1 & key))
		{//�������u�ԂȂ�
			if (pushTime[0] != 0)
			{
				return 1;
			}
			else {
				pushTime[0] = waitFrame;
			}
		}
		oldFrame[0] = (pad1 & key);
	}
	// �X�e�B�b�N���E���͂����Ƃ�
	else if (key == e_PAD_RIGHT)
	{
		if (!oldFrame[1] && (pad1 & key))
		{//�������u�ԂȂ�
			if (pushTime[1] != 0)
			{
				return 1;
			}
			else {
				pushTime[1] = waitFrame;
			}
		}
		oldFrame[1] = (pad1 & key);

		if (pushTime[1] != 0)//���������Ԃ�0����Ȃ��̂Ȃ�
		{
			pushTime[1]--;//���������Ԃ��f�N�������g
		}
	}

	if (pushTime[0] != 0)//���������Ԃ�0����Ȃ��̂Ȃ�
	{
		pushTime[0]--;//���������Ԃ��f�N�������g
	}

	return 0;
}

// main�ɏ����Ă�����

//int main()
//{
//	InputPad::Update();
//
//	// ����main.cpp�ɏ����Ă邩�珟��ɓ������Ă�����
//	// �A�ł����Ƃ�
//	if (InputPad::IsPadInputBarrage(PAD_INPUT_LEFT) ||
//		InputPad::IsPadInputBarrage(PAD_INPUT_RIGHT))
//	{
//		isDashFlag = TRUE; // �錾���K�v
//	}
//	else if (!GetJoypadInputState(PAD_INPUT_LEFT) &&
//		!GetJoypadInputState(PAD_INPUT_RIGHT))
//	{
//		isDashFlag = FALSE;
//	}
//
//	if (isDashFlag == TRUE)
//	{
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "����ɂ���");
//	}
//}