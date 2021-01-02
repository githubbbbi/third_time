#pragma once


const float NORMAL_SPEED = 4.0f;	// 通常スピード
const float DASH_SPEED = 7.0f;						// ダッシュスピード
const float GRAVITY = 0.8f;			// 重力
const float JUMP_POWER = -13.0f;	// ジャンプ力

class CharaBase
{
protected:
	float x;			// 中心座標
	float y;			// 中心座標
	float oldX;			// 1フレーム前の座標
	float oldY;			// 1フレーム前の座標
	float moveX;		// 移動量
	float moveY;		// 移動量
	float speed;		// スピード
	float gravity;		// 落下度
	int radius;			// 半径
	int graphHandle;	// 画像ハンドル
	int hp;				// HP
	int attackPower;	// 攻撃力
	bool isAlive;		// 生存フラグ
	bool isLeftWard;	// 左向きフラグ
	bool isJump;		// ジャンプフラグ
	bool isFall;		// 落下フラグ

	// キャラクタの落下
	void CharaFall();

	// キャラの移動
	void CharaMove(float hitWidth, float hitHeight);

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// HP(バッテリー)が0
	void HpZero();

	// HP管理
	void HpManager();

public:
	// コンストラクタ宣言
	CharaBase(float x, float y, int radius,
			  float speed, int hp, int attackPower, int graphHandle);

	void CharaJump();

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();
	
	// oldX座標を取得
	float GetPosOldX();

	// oldY座標を取得
	float GetPosOldY();

	// 半径を取得
	int GetRadius();

	// 攻撃力を取得
	int GetAttackPower();

	// isAliveを取得
	bool GetIsAlive();

	// isLeftWardを取得
	bool GetIsLeftWard();

	// ダメージを受ける
	void ReceiveDamage(int attackPower);

	// キャラクタ同士が接触
	void CharactersCollision();
};