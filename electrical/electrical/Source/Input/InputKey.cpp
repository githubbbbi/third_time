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
	static int presstime[256] = { 0 };
	static int prevkey[256] = { 0 };

	// キー入力がされた時から増加
	presstime[key]++;

	// キーが押された瞬間の場合
	if (!prevkey[key] && IsKeyInputNow(key))
	{
		// カウント変数
		static int i = 0;

		// カウントを増やす
		i++;

		// iが2の場合
		if (i == 2)
		{
			// 2回目のキー入力が0.3秒より小さい場合
			if (presstime[key] <= 15)
			{
				// カウントを0にセット
				i = 0;

				// presstime[]を０にしておく
				presstime[key] = 0;

				return true;
			}
			else
			{
				i = 0;

				//presstime[]を０にしておく
				presstime[key] = 0;

				return false;
			}
		}
	}

	// 今のフレームのキー入力を保存して、後のキー入力判定のとき使う
	prevkey[key] = IsKeyInputNow(key);

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