#pragma once

enum
{
	e_MOVE_LEFT,		// 左移動
	e_MOVE_RIGHT,		// 右移動
	e_JUMP,				// ジャンプ
	e_ATTACK,			// 攻撃
	e_FIXED_DIRECTION,	// 向き固定
	e_START,			// ゲーム開始
	e_EXIT,				// ゲーム終了
	e_NO_INPUT = -1,	// 入力なし
};

class InputManager
{
private:
	static bool isInputKey;	// キー入力フラグ
	static bool isInputPad;	// パッド入力フラグ

	static int keyCode;// キーコード

	InputManager();

	// キーコード変換
	static void ConversionKeyCode(int key);

public:
	// 更新処理
	static void Update();

	// 押されている場合TRUE
	static bool IsInputNow(int key);

	// 前フレームが押されていない状態から押された場合TRUE
	static bool IsInputTrigger(int key);

	// 押されていて離された瞬間TRUE
	static bool IsInputRelease(int key);

	// 連打された場合TRUE
	static bool IsInputBarrage(int key);

	// 押されていない場合
	static bool IsInputNo(int key);

	// padのinputXを取得
	static int GetPadInputX();

	// padのinputXを取得
	static int GetPadInputY();
};