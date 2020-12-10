#pragma once

// �}�b�v�`�b�v�̓����蔻��
enum MapHit
{
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
	// �}�b�v�Ƃ̓����蔻��


	// ��ʓ��ɂƂǂ܂�
	static void StayOnScreen(float *x, float *y, int radius,
							 bool isStayX, bool isStayY);

	//�}�b�v�`�b�v�̒l���擾
	static int GetMapParam(float x, float y);

	//�}�b�v�Ƃ̓����蔻��
	// 1�F���ӂɏՓˁA2�F�E�ӂɏՓˁA3�F��ӁA4�F���ӁA5�F�G�ꂽ�玀�S�A6�F���[�v
	static int MapHitCheck(float x, float y, float *moveX, float *moveY);

	// �~�̃R���W����
	static bool IsCircleCollision(float x1, float y1, int r1,
								float x2, float y2, int r2);
};