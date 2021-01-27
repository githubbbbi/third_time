#pragma once

class Effect_Lightning
{
private:
	// ��
	int posX;
	int posY;
	int posX2;
	int posY2;
	int oldPosX;
	int oldPosY;
	int oldPosX2;
	int oldPosY2;

	// ����
	int valX;
	int valY;

	// ���˕ǂ̍��W
	int wallX;
	int wallY;
	int wallX2;
	int wallY2;

	int timer;

	// �F
	typedef struct
	{
		float r;		// �ԐF				:0~255
		float g;		// �ΐF				:0~255
		float b;		// �F				:0~255
		float h;		// �F��(hue)			:0~360
		float s;		// �ʓx(saturation)	:0~255
		float v;		// ���x(value)		:0~255
	}Color;

	Color color[2];

	// �ړ�
	void Move();

	// ����
	void LightningCollision();

public:
	Effect_Lightning(int wallX, int wallY, int wallX2, int wallY2);
	~Effect_Lightning() = default;

	// �򋗗�
	bool IsLengthOver();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};