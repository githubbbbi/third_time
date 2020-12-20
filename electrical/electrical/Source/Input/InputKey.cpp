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
	static long long int presstime[2][2] = { 0 };
	static int prevkey[2] = { 0 };

	if ( key == e_KEY_MOVE_LEFT )
	{
		// キーが押された瞬間の場合
		if ( !prevkey[0] && IsKeyInputNow(key) )
		{
			static int i = 0;	// カウント変数

			// 今の時間が知りたい（ミリ秒単位で)
			presstime[0][i] = GetTickCount64();
			++i;

			// iが2の場合
			if ( i == 2 )
			{
				// ２つの時間差が0.35秒より小さい場合
				if ( presstime[0][1] - presstime[0][0] <= 0.25 * 1000 )
				{
					i = 0;

					// presstime[]を２つとも０にしておく
					presstime[0][0] = 0;
					presstime[0][1] = 0;

					return true;
				}
				else
				{
					i = 0;

					//presstime[]を２つとも０にしておく
					presstime[0][0] = 0;
					presstime[0][1] = 0;

					return false;
				}
			}
		}
		// 今のフレームのキー入力を保存して、後のキー入力判定のとき使う
		prevkey[0] = IsKeyInputNow(key);
	}
	else if ( key == e_KEY_MOVE_RIGHT )
	{
		// キーが押された瞬間の場合
		if ( !prevkey[1] && IsKeyInputNow(key) )
		{
			static int j = 0;	// カウント変数

			// 今の時間が知りたい（ミリ秒単位で)
			presstime[1][j] = GetTickCount64();
			++j;

			// iが2の場合
			if ( j == 2 )
			{
				// ２つの時間差が0.35秒より小さい場合
				if ( presstime[1][1] - presstime[1][0] <= 0.25 * 1000 )
				{
					j = 0;

					// presstime[]を２つとも０にしておく
					presstime[1][0] = 0;
					presstime[1][1] = 0;

					return true;
				}
				else
				{
					j = 0;

					//presstime[]を２つとも０にしておく
					presstime[1][0] = 0;
					presstime[1][1] = 0;

					return false;
				}
			}
		}
		// 今のフレームのキー入力を保存して、後のキー入力判定のとき使う
		prevkey[1] = IsKeyInputNow(key);
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