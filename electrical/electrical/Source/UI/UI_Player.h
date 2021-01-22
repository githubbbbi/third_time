#pragma once

class UI_Player
{
private:

	// lineの構造体の宣言
	typedef struct
	{
		float x;		// lineの中心座標
		float y;		// lineの中心座標
		float size;		// lineの縦、横の長さ
		float r;		// 赤色				:0~255
		float g;		// 緑色				:0~255
		float b;		// 青色				:0~255
		float h;		// 色相(hue)			:0~360
		float s;		// 彩度(saturation)	:0~255
		float v;		// 明度(value)		:0~255
	}Line;

	Line line[2];

	int x;	// 画像ハンドル中心座標
	int y;	// 画像ハンドル中心座標

	// hpの残量に合わせて色を変える
	void ChangeHSV(int hp, int maxHp);

public:
	UI_Player();
	~UI_Player() = default;

	void Update(int hp, int maxHp, int battery, int maxBattery);
	void Draw(int hp, int maxHp, int battery, int maxBattery);
};