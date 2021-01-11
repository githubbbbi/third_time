#pragma once

extern const float GRAVITY;		// 重力
extern const int ALIVE_TIME;

class WaterBullet
{
private:
	float x;				// 中心座標
	float y;				// 中心座標
	float moveX;			// 移動量
	float moveY;			// 移動量
	int radius;				// 半径
	double exRate;
	float speed;			// スピード
	int graphHandle;		// 画像ハンドル
	int hitFrame;			// ヒットしているフレーム数
	int aliveTimer;
	bool isAlive;			// 発射フラグ
	bool isMapHit;			// マップヒットフラグ
	bool isLeftWard;		// 左向きフラグ

public:
	WaterBullet(float x, float y, int radius,
		float speed, bool isCharaLeftWard, int graphHandle);

	// ブロックとの当たり判定を考慮した移動
	void Move();

	// 消去
	void Erase();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);

	// 弾がヒットした場合の処理
	void Hit();

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();

	// 半径を取得
	int GetRadius();

	// isAliveを取得
	bool GetIsAlive();
};