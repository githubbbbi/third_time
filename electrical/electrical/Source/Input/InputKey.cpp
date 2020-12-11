#include "DxLib.h"
#include "InputKey.h"

// 変数初期化
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

int InputKey::inputFrame = 0;

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

//// 連打された場合TRUE
//bool InputKey::IsKeyInputBarrage(int key)
//{
//	static int presstime[2] = { 0 };
//	static int prevkey = 0;
//	if (!prevkey && CheckHitKey(key))//キーが押された瞬間なら
//	{
//		static int i = 0;//カウント変数
//		static int j = 0;//カウント変数
//		presstime[i] = GetTickCount64();//今の時間が知りたい（ミリ秒単位で)
//		++i;//カウントする
//		if (i == 2)//iが2なら
//		{
//			if ((long long)presstime[1] - presstime[0] <= 0.35 * 1000)//２つの時間差が0.35秒より小さければ
//			{
//				i = 0;//iを0にする
//				presstime[0] = 0;//presstime[]を２つとも０にしておく
//				presstime[1] = 0;
//				return 1;//1を返す
//			}
//			else {
//				i = 0;//iを0にする
//				presstime[0] = 0;//presstime[]を２つとも０にしておく
//				presstime[1] = 0;
//				return 0;	//0を返す
//			}
//		}
//	}
//
//	prevkey = CheckHitKey(key);//今のフレームのキー入力を保存して、
//							//後のキー入力判定のとき使う
//	return 0;
//}
