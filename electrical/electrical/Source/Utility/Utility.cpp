#include "DxLib.h"
#include <math.h>
#include "Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

// ��ʓ��ɂƂǂ܂�
void Utility::StayOnScreen(float *x, float *y, int radius,
						   bool isStayX, bool isStayY)
{
	if ( isStayX )
	{
		if ( *x - radius < 0 )
		{
			*x = (float)0 + (float)radius;
		}
		else if ( *x + radius > MAP_COUNT_X * CHIP_SIZE )
		{
			*x = (float)(MAP_COUNT_X * CHIP_SIZE) - (float)radius;
		}
	}

	if ( isStayY )
	{
		if ( *y - radius < 0 )
		{
			*y = (float)0 + (float)radius;
		}
		else if ( *y + radius > MAP_COUNT_Y * CHIP_SIZE )
		{
			*y = (float)(MAP_COUNT_Y * CHIP_SIZE) - (float)radius;
		}
	}
}

// �}�b�v�Ƃ̓����蔻��
// 1�F���ӁA2�F�E�ӁA3�F��ӁA4�F����
int Utility::MapHitCheck(float x, float y,
						 float *moveX, float *moveY)
{
	const float value = 1.0f;

	// ���W�Ɉړ��ʂ𑫂�
	float addX = x + *moveX;
	float addY = y + *moveY;

	// �u���b�N�ɓ������Ă��邩�`�F�b�N
	if ( Stage::GetMapParam(addX, addY) == e_MAP_BLOCK )
	{
		// �������Ă����ꍇ�A�ǂ��痣��
		// �u���b�N�̏㉺���E�̍��W���v�Z
		RECT map;
		map.left = ((int)addX / CHIP_SIZE) * CHIP_SIZE;				// ���ӂ�X���W
		map.right = ((int)addX / CHIP_SIZE + 1) * CHIP_SIZE - 1;	// �E�ӂ�X���W
		map.top = ((int)addY / CHIP_SIZE) * CHIP_SIZE;				// ��ӂ�Y���W
		map.bottom = ((int)addY / CHIP_SIZE + 1) * CHIP_SIZE;		// ���ӂ�Y���W

		// ��ӂɏՓ� moveY��0.0f���傫���ꍇ�A���ɐi�����Ƃ��Ă���
		if ( *moveY > 0.0f )
		{
			// �ړ��ʂ�␳
			*moveY = (float)map.top - y - value;

			// ��ӂɏՓ˂����ƕԂ�
			return e_HIT_BLOCK_TOP;
		}

		// ���ӂɏՓ�
		if ( *moveY < 0.0f )
		{
			// �ړ��ʂ�␳
			*moveY = (float)map.bottom - y + value;

			// ���ӂɏՓ˂����ƕԂ�
			return e_HIT_BLOCK_BOTTOM;
		}

		// ���ӂɏՓ�
		if ( *moveX > 0.0f )
		{
			// �ړ��ʂ�␳
			*moveX = (float)map.left - x - value;

			// ���ӂɏՓ˂����ƕԂ�
			return e_HIT_BLOCK_LEFT;
		}

		// �E�ӂɏՓ�
		if ( *moveX < 0.0f )
		{
			// �ړ��ʂ�␳
			*moveX = (float)map.right - x + value;;

			// �E�ӂɏՓ˂����ƕԂ�
			return e_HIT_BLOCK_RIGHT;
		}
	}

	// �S�[���Ƃ̔���
	if ( Stage::GetMapParam(addX, addY) == e_MAP_GOAL )
	{
		return e_HIT_GOAL;
	}

	// �I�� �ǂ��ɂ�������Ȃ�����
	return e_HIT_NOT;
}

// �~�̃R���W����
bool Utility::IsCircleCollision(float x1, float y1, int r1,
								float x2, float y2, int r2)
{
	double disX = (double)x2 - (double)x1;
	double disY = (double)y2 - (double)y1;
	double d = sqrt(disX * disX + disY * disY);
	double r = (double)r1 + (double)r2;

	if ( d < r )
	{
		return true;
	}

	return false;
}

// ��`�̎q���W����
bool Utility::IsRectCollision(float x1, float y1, int w1, int h1,
							  float x2, float y2, int w2, int h2)
{
	float halfW1 = (float)w1 / 2.0f;
	float halfH1 = (float)h1 / 2.0f;
	float halfW2 = (float)w2 / 2.0f;
	float halfH2 = (float)h2 / 2.0f;

	if ( fabsf(x1 - x2) < halfW1 + halfW2 &&
		fabsf(y1 - y2) < halfH1 + halfH2 )
	{
		return true;
	}

	return false;
}

// �X�N���[��
void Utility::Scroll(int centerX, int centerY, int *scrollX, int *scrollY)
{
	// �X�N���[�����W���[�ɍs���ƃX�N���[��
	*scrollX = (centerX / WIN_WIDTH) * WIN_WIDTH;
	*scrollY = (centerY / WIN_HEIGHT) * WIN_HEIGHT;

	// X����
	// �}�b�v�̍��[��荶�ɂ͂����Ȃ�
	if ( *scrollX < 0 )
	{
		*scrollX = 0;
	}

	// �}�b�v�̉E�[���E�ɂ͂����Ȃ�
	if ( *scrollX + WIN_WIDTH > MAP_COUNT_X * CHIP_SIZE )
	{
		*scrollX = MAP_COUNT_X * CHIP_SIZE - WIN_WIDTH;
	}

	// Y����
	// �}�b�v�̏�[����ɂ͂����Ȃ�
	if ( *scrollY < 0 )
	{
		*scrollY = 0;
	}

	// �}�b�v�̉��[��艺�ɂ͂����Ȃ�
	if ( *scrollY + WIN_HEIGHT > MAP_COUNT_Y * CHIP_SIZE )
	{
		*scrollY = MAP_COUNT_Y * CHIP_SIZE - WIN_HEIGHT;
	}
}

// HSV����RGB�ɕϊ�
void Utility::ConvertHSVtoRGB(float *r, float *g, float *b,
							  float h, float s, float v)
{
	float max = v;
	float min = max - (s / 255.0f) * max;

	if ( h >= 0 && h <= 60 )
	{
		*r = max;
		*g = (h / 60.0f) * (max - min) + min;
		*b = min;
	}
	else if ( h <= 120 )
	{
		*r = ((120.0f - h) / 60.0f) * (max - min) + min;
		*g = max;
		*b = min;
	}
	else if ( h <= 180 )
	{
		*r = min;
		*g = max;
		*b = ((h - 120.0f) / 60.0f) * (max - min) + min;
	}
	else if ( h <= 240 )
	{
		*r = min;
		*g = ((240.0f - h) / 60.0f) * (max - min) + min;
		*b = max;
	}
	else if ( h <= 300 )
	{
		*r = ((h - 240.0f) / 60.0f) * (max - min) + min;
		*g = min;
		*b = max;
	}
	else if ( h <= 360 )
	{
		*r = max;
		*g = min;
		*b = ((360.0f - h) / 60.0f) * (max - min) + min;
	}
}