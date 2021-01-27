#pragma once

class Effect_Lightning
{
private:
	// 線
	int posX;
	int posY;
	int posX2;
	int posY2;
	int oldPosX;
	int oldPosY;
	int oldPosX2;
	int oldPosY2;

	// 方向
	int valX;
	int valY;

	// 反射壁の座標
	int wallX;
	int wallY;
	int wallX2;
	int wallY2;

	int timer;

	// 色
	typedef struct
	{
		float r;		// 赤色				:0~255
		float g;		// 緑色				:0~255
		float b;		// 青色				:0~255
		float h;		// 色相(hue)			:0~360
		float s;		// 彩度(saturation)	:0~255
		float v;		// 明度(value)		:0~255
	}Color;

	Color color[2];

	// 移動
	void Move();

	// 反射
	void LightningCollision();

public:
	Effect_Lightning(int wallX, int wallY, int wallX2, int wallY2);
	~Effect_Lightning() = default;

	// 飛距離
	bool IsLengthOver();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};