#pragma once

class CharacterBase
{
protected:
	int x, y;// 中心座標
	int moveX, moveY;// 移動量
	int speed;// スピード
	int radius;// 半径
	int graphHandle;// 画像ハンドル

	bool isAlive;// 生存フラグ
	bool isLeftWard;// 左向きフラグ

	bool isJump;// ジャンプフラグ

	// マップとの当たり判定
	void MapCollision();

public:
	// コンストラクタ宣言
	CharacterBase(int x, int y, int speed, 
				  int radius, int graphHandle);

	// 初期化処理
	virtual void Initialize() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw() = 0;
};