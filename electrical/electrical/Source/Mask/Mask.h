#pragma once

extern const double EX_RATE_UP_SPEED;	// �g��X�s�[�h
extern const double EX_RATE_DOWN_SPEED;	// ���k�X�s�[�h
extern const double MAX_EX_RATE;		// �ő�g�嗦
extern const double MIN_EX_RATE;		// �ŏ��g�嗦

class Mask
{
private:
	static int screenHandle;

	static double exRate;	// �g�嗦

public:
	// �}�X�N�̃Z�b�g
	static void SetMask();

	// �}�X�N�̊g��
	static bool MaskScaleUp();

	// �}�X�N�̏k��
	static bool MaskScaleDown();

	// �}�X�N�̕`��
	static void DrawMask();

	// �}�X�N�̌㏈��
	static void LoopMask();

	// �g�嗦���ő�̔���
	static bool IsExRateMax();

	// �g�嗦���ŏ��̔���
	static bool IsExRateMin();
};