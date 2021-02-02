#pragma once

extern const double EX_RATE_UP_SPEED;	// 拡大スピード
extern const double EX_RATE_DOWN_SPEED;	// 収縮スピード
extern const double MAX_EX_RATE;		// 最大拡大率
extern const double MIN_EX_RATE;		// 最小拡大率

class Mask
{
private:
	static int screenHandle;

	static double exRate;	// 拡大率

public:
	// マスクのセット
	static void SetMask();

	// マスクの拡大
	static bool MaskScaleUp();

	// マスクの縮小
	static bool MaskScaleDown();

	// マスクの描画
	static void DrawMask();

	// マスクの後処理
	static void PostMask();

	// 拡大率が最大の判定
	static bool IsExRateMax();

	// 拡大率が最小の判定
	static bool IsExRateMin();
};