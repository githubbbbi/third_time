#pragma once

class InputPad
{
private:
	static int pad1;// �p�b�h1�̓��͏��
	static int oldPad1;// 1�t���[���O�̃p�b�h1�̓��͏��

	InputPad();

public:
	// �X�V����
	static void PadUpdate();

	// ������Ă���ꍇTRUE
	static bool IsPadInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsPadInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsPadInputRelease(int key);
};