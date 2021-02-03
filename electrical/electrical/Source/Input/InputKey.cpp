#include "InputKey.h"

// 変数初期化
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

// 更新処理
void InputKey::Update()
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

// 連打された場合TRUE
bool InputKey::IsKeyInputBarrage(int key)
{
	// 押した時間を計測するための変数
	static int pushTime[256] = { 0 };

	// 前のフレームを判定するための変数
	static int oldFrame[256] = { 0 };

	// 再びキー入力があるまで待てるフレーム数
	const int waitFrame = 15;

	if ( !oldFrame[key] && keys[key] )
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

	oldFrame[key] = keys[key];

	// 押した時間が0じゃないなら
	if ( pushTime[key] != 0 )
	{
		// 押した時間をデクリメント
		pushTime[key]--;
	}

	return false;
}

// 押されていない場合
bool InputKey::IsKeyInputNot(int key)
{
	if ( !keys[key] )
	{
		return true;
	}

	return false;
}