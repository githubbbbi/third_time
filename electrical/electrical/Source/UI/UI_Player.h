#pragma once

class UI_Player
{
private:
	// line�̍\���̂̐錾
	typedef struct
	{
		float x;		// line�̒��S���W
		float y;		// line�̒��S���W
		float size;		// line�̏c�A���̒���
		float r;		// �ԐF				:0~255
		float g;		// �ΐF				:0~255
		float b;		// �F				:0~255
		float h;		// �F��(hue)			:0~360
		float s;		// �ʓx(saturation)	:0~255
		float v;		// ���x(value)		:0~255
	}Line;

	Line line[2];

	int x;	// �摜�n���h�����S���W
	int y;	// �摜�n���h�����S���W

	// hp�̎c�ʂɍ��킹�ĐF��ς���
	void ChangeHSV(int hp, int maxHp);

public:
	UI_Player();
	~UI_Player() = default;

	void Update(int hp, int maxHp, int battery, int maxBattery);
	void Draw(int hp, int maxHp, int battery, int maxBattery);
};