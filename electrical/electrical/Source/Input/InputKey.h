#pragma once

class InputKey
{
private:
	InputKey();

	// 最新のキーボード情報
	static char keys[256];

	// 1フレーム前のキーボード情報
	static char oldkeys[256];

public:
	// 更新処理
	static void KeyUpdate();

	// 前フレームが押されていない状態から押された場合TRUE
	static bool IsKeyInputNow(int key);

	// 押されていて離された瞬間TRUE
	static bool IsKeyInputRelease(int key);
};