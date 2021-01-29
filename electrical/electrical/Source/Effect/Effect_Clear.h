#pragma once

class Effect_Clear
{
private:
	float x;		// ���S���W
	float y;		// ���S���W
	double exRate;	// �g�嗦
	double angle;	// �p�x
	bool isActive;	// TRUE�̏ꍇ�A�A�N�e�B�u
	float r;		// �ԐF				:0~255
	float g;		// �ΐF				:0~255
	float b;		// �F				:0~255
	float h;		// �F��(hue)			:0~360
	float s;		// �ʓx(saturation)	:0~255
	float v;		// ���x(value)		:0~255
	float playerX;	// �v���C���[�̒��S���W
	float playerY;	// �v���C���[�̒��S���W

public:
	Effect_Clear(float x, float y);
	~Effect_Clear() = default;

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);

	// isActive���擾
	bool GetIsActive();
};