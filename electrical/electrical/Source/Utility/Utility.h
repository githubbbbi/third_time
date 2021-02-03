#pragma once

// �}�b�v�`�b�v�̓����蔻��
enum MapHit
{
	e_HIT_NOT,			// �Ȃ�
	e_HIT_BLOCK_LEFT,	// �u���b�N�̍���
	e_HIT_BLOCK_RIGHT,	// �u���b�N�̉E��
	e_HIT_BLOCK_TOP,	// �u���b�N�̏㑤
	e_HIT_BLOCK_BOTTOM,	// �u���b�N�̉���
	e_HIT_GOAL			// �S�[��
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
					   int *scrollX, int *scrollY, bool *isScroll);

	// �I�u�W�F�N�g���X�N���[���̒��S�ɂ��炷
	static void DisplaceObjScrnCntr(int scrollX, int scrollY,
									int screenX, int screenY, int *displaceX, int *displaceY);

	// HSV����RGB�ɕϊ�
	static void ConvertHSVtoRGB(float *r, float *g, float *b,
								float h, float s, float v);
};