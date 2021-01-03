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
	// �ϐ��錾
	// �L�����N�^�̈ړ��ʂ𑫂�
	float addX, addY;

	// �}�b�v�`�b�v�㉺���E�̍��W
	RECT map;

	// ���W�Ɉړ��ʂ𑫂�
	addX = x + *moveX;
	addY = y + *moveY;

	// �u���b�N�ɓ������Ă��邩�`�F�b�N
	if ( Stage::GetMapParam(addX, addY) == e_MAP_BLOCK )
	{
		// �������Ă����ꍇ�A�ǂ��痣��
		// �u���b�N�̏㉺���E�̍��W���v�Z
		map.left = ((int)addX / CHIP_SIZE) * CHIP_SIZE;			// ���ӂ�X���W
		map.right = ((int)addX / CHIP_SIZE + 1) * CHIP_SIZE;	// �E�ӂ�X���W
		map.top = ((int)addY / CHIP_SIZE) * CHIP_SIZE;			// ��ӂ�Y���W
		map.bottom = ((int)addY / CHIP_SIZE + 1) * CHIP_SIZE;	// ���ӂ�Y���W

		// ��ӂɏՓ� *moveY��0.0f���傫���ꍇ�A���ɐi�����Ƃ��Ă���
		if ( *moveY > 0.0f )
		{
			// �ړ��ʂ�␳
			*moveY = map.top - y - 1.0f;

			// ��ӂɏՓ˂����ƕԂ�
			return e_HIT_TOP;
		}

		// ���ӂɏՓ�
		if ( *moveY < 0.0f )
		{
			// �ړ��ʂ�␳
			*moveY = map.bottom - y + 1.0f;

			// ���ӂɏՓ˂����ƕԂ�
			return e_HIT_BOTTOM;
		}

		// ���ӂɏՓ�
		if ( *moveX > 0.0f )
		{
			// �ړ��ʂ�␳
			*moveX = 0.0f;

			// ���ӂɏՓ˂����ƕԂ�
			return e_HIT_LEFT;
		}

		// �E�ӂɏՓ�
		if ( *moveX < 0.0f )
		{
			// �ړ��ʂ�␳
			*moveX = 0.0f;

			// �E�ӂɏՓ˂����ƕԂ�
			return e_HIT_RIGHT;
		}
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

// �V�F�C�N
void Utility::Shake(float *shakeX, float *shakeY,
					float *addX, float *addY)
{
	// X����
	*shakeX = (rand() % ((int)*addX - ((int)-*addX) + 1)) + (-*addX);

	if ( *addX > 0 )
	{
		*addX -= SHAKE_DECREASE;
	}

	if ( *addX < 0 )
	{
		*addX = 0;
	}

	// Y����
	*shakeY = (rand() % ((int)*addY - ((int)-*addY) + 1)) + (-*addY);

	if ( *addY > 0 )
	{
		*addY -= SHAKE_DECREASE;
	}

	if ( *addY < 0 )
	{
		*addY = 0;
	}
}

// �X�N���[��
void Utility::Scroll(int centerX, int centerY, int *scrollX, int *scrollY)
{
	// �w����W�𒆐S�ɃX�N���[���ʂ�����
	*scrollX = centerX - WIN_WIDTH / 2;
	*scrollY = centerY - WIN_HEIGHT / 2;

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