#include "DxLib.h"
#include "InputPad.h"

// 変数初期化
int InputPad::pad1 = 0;
int InputPad::oldPad1 = 0;

// 更新処理
void InputPad::Update()
{
	oldPad1 = pad1;
	pad1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);
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