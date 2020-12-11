#pragma once

class ElectricGun
{
private:
	float x;			// 中心座標
	float y;			// 中心座標
	int radius;			// 半径
	float speed;		// スピード
	int graphHandle;	// 画像ハンドル
	bool isAlive;		// 発射フラグ
	bool isCharaLeftWard;	// キャラクタの左向きフラグ

public:
	ElectricGun(float x, float y, int radius,
				float speed, bool isCharaLeftWard, int graphHandle);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 弾がヒットした場合の処理
	void BulletHit();

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();

	// 半径を取得
	int GetRadius();

	// isAliveを取得
	bool GetIsAlive();
};