#pragma once

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;			// HP減少タイム
const int HP_CHARGE_TIME = (60 * 1) / 2;	// HPチャージタイム

const float DASH_SPEED = 7.0f;// ダッシュスピード

const int PLAYER_MAX_HP = 100;	// 最大HP

const int PLAYER_CONSUMPTION_BULLET_NUM = 5;	// 電力を消費する弾数

class Chara_Player:public CharaBase
{
private:
	int hpTimer;		// HP(バッテリー)タイマー
	int chargeTimer;	// HP(バッテリー)チャージタイマー
	int shotBulletNum;	// 撃った弾数

	bool isRelease;		// キー入力がなかった時にtrue

	// 移動
	void Move();

	// HP(バッテリー)減少
	void HpDcrease();

	// HP(バッテリー)チャージ
	void HpCharge();

	// HP管理
	void HpManager();

public:
	Chara_Player(float x, float y, int radius,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(float shakeX, float shakeY);

	// 攻撃
	bool IsAttack();
};