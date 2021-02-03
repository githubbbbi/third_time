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
	float r;			// 赤色				:0~255
	float g;			// 緑色				:0~255
	float b;			// 青色				:0~255
	float h;			// 色相(hue)			:0~360
	float s;			// 彩度(saturation)	:0~255
	float v;			// 明度(value)		:0~255

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
	void Draw(int scrollX, int scrollY,
			  int displaceX, int  displaceY);

	// isActiveを取得
	bool GetIsActive();
};