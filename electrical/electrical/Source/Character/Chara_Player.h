#pragma once

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;// HP減少タイム
const int HP_CHARGE_TIME = (60 * 1) / 2;// HPチャージタイム

const int MAX_HP = 100;

// キーボードのキーコンフィグ
enum KeyConfig
{
	e_KEY_LEFT = KEY_INPUT_LEFT,	// 左移動
	e_KEY_RIGHT = KEY_INPUT_RIGHT,	// 右移動
	e_KEY_JUMP = KEY_INPUT_UP,		// ジャンプ
	e_KEY_ATTACK = KEY_INPUT_SPACE,	// 攻撃
};

// パッドのキーコンフィグ
enum PadConfig
{
	e_PAD_LEFT = PAD_INPUT_LEFT,	// 左移動
	e_PAD_RIGHT = PAD_INPUT_RIGHT,	// 右移動
	e_PAD_JUMP = PAD_INPUT_1,		// ジャンプ
	e_PAD_ATTACK = PAD_INPUT_3,		// 攻撃
};

class Chara_Player:public CharaBase
{
private:
	int hpTimer;// HP(バッテリー)タイマー
	int chargeTimer;// HP(バッテリー)チャージタイマー

	// 移動
	void Move();

	// HP(バッテリー)減少
	void HpDcrease();

	// HP(バッテリー)チャージ
	bool HpCharge();

public:
	Chara_Player(int x, int y, int radius,
				 int speed, int hp, int graphHandle);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};