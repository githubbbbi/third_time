#pragma once

class Mask
{
private:
	static int screenHandle;

	static double sizeRate;

public:
	// �}�X�N�̃Z�b�g
	static void SetMask();

	// �}�X�N�̎��k
	static void MaskShrink();

	// �}�X�N�̕`��
	static void DrawMask();

	// �}�X�N�̌㏈��
	static void LoopMask();
};