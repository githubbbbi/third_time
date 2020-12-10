#pragma once

// 重力
extern const float GRAVITY;

// ジャンプ力
extern const float JUMP_POWER;

class CharaBase
{
protected:
	float x, y;			// 中心座標
	float moveX, moveY;	// 移動量
	float speed;		// スピード
	float gravity;		// 落下度
	int radius;			// 半径
	int graphHandle;	// 画像ハンドル

	int hp;	// HP
	int attackPower;// 攻撃力

	bool isAlive;		// 生存フラグ
	bool isLeftWard;	// 左向きフラグ

	bool isJump;		// ジャンプフラグ

	// キャラクタの落下
	void CharaFall();

	// キャラの移動
	void CharaMove();

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// HP(バッテリー)が0
	void HpZero();

public:
	// コンストラクタ宣言
	CharaBase(float x, float y, int radius,
			  float speed, int hp, int attackPower, int graphHandle);

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();

	// 半径を取得
	int GetRadius();

	// 攻撃力を取得
	int GetAttackPower();
};