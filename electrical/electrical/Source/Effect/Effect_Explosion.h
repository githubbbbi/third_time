#pragma once

class Effect_Explosion
{
private:
	float x;			// 中心座標
	float y;			// 中心座標
	float speed;		// スピード
	double exRate;		// 拡大率
	double randAngle;	// 角度
	int frame;			// フレーム数
	int blendValue;		// ブレンド値
	int blendDecrease;	// ブレンド減少値
	bool isActive;		// TRUEの場合、アクティブ

	int number;

	// 移動
	void Move();

	// 消去
	void Erase();

public:
	Effect_Explosion(float x, float y, int blendDecrease);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);

	// isActiveを取得
	bool GetIsActive();
};