#pragma once

// パッドのキーコンフィグ
enum PadConfig
{
	e_PAD_LEFT = PAD_INPUT_LEFT,	// 左移動
	e_PAD_RIGHT = PAD_INPUT_RIGHT,	// 右移動
	e_PAD_JUMP = PAD_INPUT_1,		// ジャンプ
	e_PAD_ATTACK = PAD_INPUT_3,		// 攻撃
};

class InputPad
{
private:
	static int pad1;	// パッド1の入力状態
	static int oldPad1;	// 1フレーム前のパッド1の入力状態

	InputPad();

public:
	// 更新処理
	static void Update();

	// 押されている場合TRUE
	static bool IsPadInputNow(int key);

	// 前フレームが押されていない状態から押された場合TRUE
	static bool IsPadInputTrigger(int key);

	// 押されていて離された瞬間TRUE
	static bool IsPadInputRelease(int key);
};