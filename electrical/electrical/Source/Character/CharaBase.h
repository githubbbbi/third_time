#pragma once

class CharaBase
{
protected:
	int x, y;// 中心座標
	int moveX, moveY;// 移動量
	int speed;// スピード
	int radius;// 半径
	int graphHandle;// 画像ハンドル

	int hp;// HP

	bool isAlive;// 生存フラグ
	bool isLeftWard;// 左向きフラグ

	bool isJump;// ジャンプフラグ

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// マップとの当たり判定
	void MapCollision();

public:
	// コンストラクタ宣言
	CharaBase(int x, int y, int radius,
			  int speed, int hp, int graphHandle);

	// X座標を取得
	int GetPosX();

	// Y座標を取得
	int GetPosY();

	// 半径を取得
	int GetRadius();

	//// 初期化処理
	//virtual void Initialize() = 0;

	//// 更新処理
	//virtual void Update() = 0;

	//// 描画処理
	//virtual void Draw() = 0;
};