#pragma once

#include <vector>

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;			// HP減少タイム
const int HP_CHARGE_TIME = (60 * 1) / 2;	// HPチャージタイム

const int PLAYER_MAX_HP = 100;

class Chara_Player:public CharaBase
{
private:
	int hpTimer;		// HP(バッテリー)タイマー
	int chargeTimer;	// HP(バッテリー)チャージタイマー

	int bulletGraphHandle;// 弾画像ハンドル

	struct Bullet
	{
		float x;			// 中心座標
		float y;			// 中心座標
		int radius;			// 半径
		float speed;		// スピード
		int graphHandle;	// 画像ハンドル
		bool isAlive;		// 発射フラグ

		Bullet(float x, float y, int radius,
			   float speed, int graphHandle);

		void Update();
		void Draw();
	};

	std::vector<Bullet *> bullets;

	// 移動
	void Move();

	// HP(バッテリー)減少
	void HpDcrease();

	// HP(バッテリー)チャージ
	void HpCharge();

	// HP管理
	void HpManager();

	// 攻撃
	void Attack();

public:
	Chara_Player(float x, float y, int radius,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};