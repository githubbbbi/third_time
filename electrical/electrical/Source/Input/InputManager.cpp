#include "InputManager.h"
#include "InputKey.h"
#include "InputPad.h"

// 変数初期化
bool InputManager::isInputKey = false;
bool InputManager::isInputPad = false;

int InputManager::keyCode = 0;

// キーコード変換
void InputManager::ConversionKeyCode(int key)
{
	// キーボード
	if ( isInputKey )
	{
		if ( key == e_MOVE_LEFT )
		{
			keyCode = e_KEY_MOVE_LEFT;
		}
		else if ( key == e_MOVE_RIGHT )
		{
			keyCode = e_KEY_MOVE_RIGHT;
		}
		else if ( key == e_DASH )
		{
			keyCode = e_KEY_DASH;
		}
		else if ( key == e_JUMP )
		{
			keyCode = e_KEY_JUMP;
		}
		else if ( key == e_ATTACK )
		{
			keyCode = e_KEY_ATTACK;
		}
		else if ( key == e_LOCK )
		{
			keyCode = e_KEY_LOCK;
		}
		else if ( key == e_HELP )
		{
			keyCode = e_KEY_HELP;
		}
		else if ( key == e_START )
		{
			keyCode = e_KEY_START;
		}
		else if ( key == e_EXIT )
		{
			keyCode = e_KEY_EXIT;
		}
		else
		{
			keyCode = e_NO_INPUT;
		}
	}

	// パッド
	if ( isInputPad )
	{
		if ( key == e_MOVE_LEFT )
		{
			keyCode = e_PAD_MOVE_LEFT;
		}
		else if ( key == e_MOVE_RIGHT )
		{
			keyCode = e_PAD_MOVE_RIGHT;
		}
		else if ( key == e_DASH )
		{
			keyCode = e_PAD_DASH;
		}
		else if ( key == e_JUMP )
		{
			keyCode = e_PAD_JUMP;
		}
		else if ( key == e_ATTACK )
		{
			keyCode = e_PAD_ATTACK;
		}
		else if ( key == e_LOCK )
		{
			keyCode = e_PAD_LOCK;
		}
		else if ( key == e_HELP )
		{
			keyCode = e_PAD_HELP;
		}
		else if ( key == e_START )
		{
			keyCode = e_PAD_START;
		}
		else if ( key == e_EXIT )
		{
			keyCode = e_PAD_EXIT;
		}
		else
		{
			keyCode = e_NO_INPUT;
		}
	}
}

// 更新処理
void InputManager::Update()
{
	// キーボード
	if ( CheckHitKeyAll() )
	{
		isInputKey = true;
		isInputPad = false;
	}

	// パッド
	if ( GetJoypadInputState(DX_INPUT_PAD1) )
	{
		isInputPad = true;
		isInputKey = false;
	}

	InputKey::Update();
	InputPad::Update();
}

// 押されている場合TRUE
bool InputManager::IsInputNow(int key)
{
	ConversionKeyCode(key);

	// キーボード入力
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputNow(keyCode) )
		{
			return true;
		}
	}

	// パッド入力
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputNow(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// 前フレームが押されていない状態から押された場合TRUE
bool InputManager::IsInputTrigger(int key)
{
	ConversionKeyCode(key);

	// キーボード入力
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputTrigger(keyCode) )
		{
			return true;
		}
	}

	// パッド入力
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputTrigger(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// 押されていて離された瞬間TRUE
bool InputManager::IsInputRelease(int key)
{
	ConversionKeyCode(key);

	// キーボード入力
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputRelease(keyCode) )
		{
			return true;
		}
	}

	// パッド入力
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputRelease(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// 連打された場合TRUE
bool InputManager::IsInputBarrage(int key)
{
	ConversionKeyCode(key);

	// キーボード入力
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputBarrage(keyCode) )
		{
			return true;
		}
	}

	// パッド入力
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputBarrage(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// 押されていない場合
bool InputManager::IsInputNot(int key)
{
	ConversionKeyCode(key);

	// キーボード入力
	if ( isInputKey )
	{
		if ( InputKey::IsKeyInputNot(keyCode) )
		{
			return true;
		}
	}

	// パッド入力
	if ( isInputPad )
	{
		if ( InputPad::IsPadInputNot(keyCode) )
		{
			return true;
		}
	}

	return false;
}

// padのinputXを取得
int InputManager::GetPadInputX()
{
	return InputPad::GetInputX();
}

// padのinputXを取得
int InputManager::GetPadInputY()
{
	return InputPad::GetInputY();
}

// isInputKeyを取得
bool InputManager::GetIsInputKey()
{
	return isInputKey;
}

// isInputPadを取得
bool InputManager::GetIsInputPad()
{
	return isInputPad;
}