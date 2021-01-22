#pragma once

class UI_Player
{
private:
	int x;		// ���S���W
	int y;		// ���S���W
	float r;	// �ԐF				:0~255
	float g;	// �ΐF				:0~255
	float b;	// �F				:0~255
	float h;	// �F��(hue)			:0~360
	float s;	// �ʓx(saturation)	:0~255
	float v;	// ���x(value)		:0~255

public:
	UI_Player();
	~UI_Player() = default;

	void Update(int hp, int maxHp, int battery, int maxBattery);
	void Draw(int hp, int maxHp, int battery, int maxBattery);
};