#pragma once

class InputKey
{
private:
	static char keys[256];// �ŐV�̃L�[�{�[�h���
	static char oldKeys[256];// 1�t���[���O�̃L�[�{�[�h���

	InputKey();

public:
	// �X�V����
	static void KeyUpdate();

	// ������Ă���ꍇTRUE
	static bool IsKeyInputNow(int key);

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsKeyInputTrigger(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsKeyInputRelease(int key);
};