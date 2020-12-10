#pragma once

// キーボードのキーコンフィグ
enum KeyConfig
{
	e_KEY_LEFT = KEY_INPUT_LEFT,	// 左移動
	e_KEY_RIGHT = KEY_INPUT_RIGHT,	// 右移動
	e_KEY_JUMP = KEY_INPUT_UP,		// ジャンプ
	e_KEY_ATTACK = KEY_INPUT_SPACE,	// 攻撃
};

class InputKey
{
private:
	static char keys[256];		// 最新のキーボード情報
	static char oldKeys[256];	// 1フレーム前のキーボード情報

	InputKey();

public:
	// 更新処理
	static void Update();

	// 押されている場合TRUE
	static bool IsKeyInputNow(int key);

	// 前フレームが押されていない状態から押された場合TRUE
	static bool IsKeyInputTrigger(int key);

	// 押されていて離された瞬間TRUE
	static bool IsKeyInputRelease(int key);
};