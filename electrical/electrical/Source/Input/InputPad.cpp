#include "DxLib.h"
#include "InputPad.h"
#include "InputKey.h"

// 変数初期化
int InputPad::pad1 = 0;
int InputPad::oldPad1 = 0;

int InputPad::inputX = 0;
int InputPad::inputY = 0;

// 更新処理
void InputPad::Update()
{
	oldPad1 = pad1;
	pad1 = GetJoypadInputState(DX_INPUT_PAD1);

	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_KEY_PAD1);
}

// 押されている場合TRUE
bool InputPad::IsPadInputNow(int key)
{
	if ( (pad1 & key) )
	{
		return true;
	}

	return false;
}

// 前フレームが押されていない状態から押された場合TRUE
bool InputPad::IsPadInputTrigger(int key)
{
	if ( !(oldPad1 & key) && (pad1 & key) )
	{
		return true;
	}

	return false;
}

// 押されていて離された瞬間TRUE
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
	//押した時間を計測するための変数
	static int pushTime[2] = { 0 };
	//前のフレームを判定するための変数
	static int oldFrame[2] = { 0 };
	//再びキー入力があるまで待てるフレーム数
	const int waitFrame = 15;

	// スティックを左入力したとき
	if (key == e_PAD_LEFT)
	{
		if (!oldFrame[0] && (pad1 & key))
		{//押した瞬間なら
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
	// スティックを右入力したとき
	else if (key == e_PAD_RIGHT)
	{
		if (!oldFrame[1] && (pad1 & key))
		{//押した瞬間なら
			if (pushTime[1] != 0)
			{
				return 1;
			}
			else {
				pushTime[1] = waitFrame;
			}
		}
		oldFrame[1] = (pad1 & key);

		if (pushTime[1] != 0)//押した時間が0じゃないのなら
		{
			pushTime[1]--;//押した時間をデクリメント
		}
	}

	if (pushTime[0] != 0)//押した時間が0じゃないのなら
	{
		pushTime[0]--;//押した時間をデクリメント
	}

	return 0;
}

// mainに書いてた処理

//int main()
//{
//	InputPad::Update();
//
//	// 今はmain.cppに書いてるから勝手に動かしていいよ
//	// 連打したとき
//	if (InputPad::IsPadInputBarrage(PAD_INPUT_LEFT) ||
//		InputPad::IsPadInputBarrage(PAD_INPUT_RIGHT))
//	{
//		isDashFlag = TRUE; // 宣言が必要
//	}
//	else if (!GetJoypadInputState(PAD_INPUT_LEFT) &&
//		!GetJoypadInputState(PAD_INPUT_RIGHT))
//	{
//		isDashFlag = FALSE;
//	}
//
//	if (isDashFlag == TRUE)
//	{
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "こんにちは");
//	}
//}