#include "FrameRate.h"
#include "DxLib.h"
#include "../Input/InputKey.h"

// 変数初期化
long long FrameRate::baseTime = 0;
long long FrameRate::fpsBaseTime = 0;
float FrameRate::fps = 0.0f;

// 初期化処理
void FrameRate::Initialize()
{
	baseTime = GetNowHiPerformanceCount();
	fpsBaseTime = GetNowHiPerformanceCount();
	fps = 0.0f;
}

// FPSを計算
void FrameRate::CalcFPS()
{
	// フレーム数
	static int count = 0;
	count++;

	// 現在時刻を取得(マイクロ秒)
	long long currentTime = GetNowHiPerformanceCount();

	// 基準時刻を現在時刻に設定
	baseTime = currentTime;

	// 1秒経過
	const int time = 1000000;
	if ( currentTime - fpsBaseTime >= time )
	{
		fps = (float)(count * time) / (float)(currentTime - fpsBaseTime);
		fpsBaseTime = currentTime;	// 基準時刻を現在時刻に設定
		count = 0;					// リセット
	}
}

// FPSを表示
void FrameRate::DrawFPS()
{
	// デバッグ表示
	static bool isDrawFPS = false;
	if ( InputKey::IsKeyInputTrigger(KEY_INPUT_F1) )
	{
		isDrawFPS = !isDrawFPS;
	}

	if ( isDrawFPS )
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.ffps\n", fps);
	}
}