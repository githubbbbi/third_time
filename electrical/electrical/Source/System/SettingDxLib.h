#pragma once

class SettingDxLib
{
private:
	static long long baseTime;				// 基準となる時刻
	static int refreshRate;					// リフレッシュレート
	static unsigned long long frequency;	// 周波数

	SettingDxLib();

	// 初期化処理
	static void Initialize();

	// スリープ(Vsync未使用時にFPSを固定可能)
	static void MySleep(int flag);
public:
	// DxLibの初期化
	static bool InitDxLib();

	// DxLibの描画処理
	static bool DrawDxLib();
};