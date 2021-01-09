#pragma once

const float SHAKE_DECREASE = 0.3f;	// �U���̌�����

// �}�b�v�`�b�v�̓����蔻��
enum MapHit
{
	e_HIT_NOT,
	e_HIT_LEFT,
	e_HIT_RIGHT,
	e_HIT_TOP,
	e_HIT_BOTTOM
};

class Utility
{
private:
	Utility();

public:
	// ��ʓ��ɂƂǂ܂�
	static void StayOnScreen(float *x, float *y, int radius,
							 bool isStayX, bool isStayY);

	//�}�b�v�Ƃ̓����蔻��
	// 1�F���ӁA2�F�E�ӁA3�F��ӁA4�F����
	static int MapHitCheck(float x, float y, float *moveX, float *moveY);

	// �~�̃R���W����
	static bool IsCircleCollision(float x1, float y1, int r1,
								  float x2, float y2, int r2);

	// ��`�̃R���W����
	static bool IsRectCollision(float x1, float y1, int w1, int h1,
								float x2, float y2, int w2, int h2);

	// �X�N���[��
	static void Scroll(int centerX, int centerY,
					   int *scrollX, int *scrollY);

	// HSV����RGB�ɕϊ�
	static void ConvertHSVtoRGB(float *r, float *g, float *b,
								float h, float s, float v);
};