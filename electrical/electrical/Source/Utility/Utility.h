#pragma once

class Utility
{
private:
	Utility();

public:
	// �}�b�v�Ƃ̓����蔻��


	// ��ʓ��ɂƂǂ܂�
	static void StayOnScreen(int *x, int *y, int radius,
							 bool isStayX, bool isStayY);

	// �~�̃R���W����
	static bool CircleCollision(int x1, int y1, int r1,
						 int x2, int y2, int r2);
};