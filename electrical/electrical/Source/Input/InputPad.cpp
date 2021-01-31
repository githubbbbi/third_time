#include "InputPad.h"

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

// 2回連打でTRUE
bool InputPad::IsPadInputBarrage(int key)
{
	// 押した時間を計測するための変数
	static int pushTime[256] = { 0 };

	// 前のフレームを判定するための変数
	static int oldFrame[256] = { 0 };

	// 再びキー入力があるまで待てるフレーム数
	const int waitFrame = 30;

	if ( !oldFrame[key] && (pad1 & key) )
	{
		// 押した瞬間なら
		if ( pushTime[key] != 0 )
		{
			return true;
		}
		else
		{
			pushTime[key] = waitFrame;
		}
	}

	oldFrame[key] = (pad1 & key);

	// 押した時間が0じゃないなら
	if ( pushTime[key] != 0 )
	{
		// 押した時間をデクリメント
		pushTime[key]--;
	}

	return false;
}

// 押されていない場合
bool InputPad::IsPadInputNot(int key)
{
	if ( !(pad1 & key) )
	{
		return true;
	}

	return false;
}

// padのinputXを取得
int InputPad::GetInputX()
{
	return inputX;
}

// padのinputYを取得
int InputPad::GetInputY()
{
	return inputY;
}