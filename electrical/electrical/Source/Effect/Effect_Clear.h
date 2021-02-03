#pragma once

class Effect_Clear
{
private:
	float x;			// 中心座標
	float y;			// 中心座標
	double exRate;		// 拡大率
	double angle;		// 角度
	float speed;		// スピード
	int transparency;	// 透明度
	bool isActive;		// TRUEの場合、アクティブ
	float r;			// 赤色				:0~255
	float g;			// 緑色				:0~255
	float b;			// 青色				:0~255
	float h;			// 色相(hue)			:0~360
	float s;			// 彩度(saturation)	:0~255
	float v;			// 明度(value)		:0~255
	float playerX;		// プレイヤーの中心座標
	float playerY;		// プレイヤーの中心座標

public:
	Effect_Clear(float x, float y);
	~Effect_Clear() = default;

	// 移動
	void Move();

	// 消去
	void Erase();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY,
			  int displaceX, int  displaceY);

	// isActiveを取得
	bool GetIsActive();
};