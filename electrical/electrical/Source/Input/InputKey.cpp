#include "DxLib.h"
#include "InputKey.h"

// 変数初期化
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

// 更新処理
void InputKey::KeyUpdate()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for ( int i = 0; i < 256; i++ )
	{
		oldKeys[i] = keys[i];
	}

	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

// 押されている場合TRUE
bool InputKey::IsKeyInputNow(int key)
{
	if ( keys[key] )
	{
		return true;
	}

	return false;
}

// 前フレームが押されていない状態から押された場合TRUE
bool InputKey::IsKeyInputTrigger(int key)
{
	if ( !oldKeys[key] && keys[key] )
	{
		return true;
	}

	return false;
}

// 押されていて離された場合TRUE
bool InputKey::IsKeyInputRelease(int key)
{
	if ( oldKeys[key] && !keys[key] )
	{
		return true;
	}

	return false;
}