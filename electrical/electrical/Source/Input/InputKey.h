#pragma once

class InputKey
{
private:
	InputKey();

	// �ŐV�̃L�[�{�[�h���
	static char keys[256];

	// 1�t���[���O�̃L�[�{�[�h���
	static char oldkeys[256];

public:
	// �X�V����
	static void KeyUpdate();

	// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
	static bool IsKeyInputNow(int key);

	// ������Ă��ė����ꂽ�u��TRUE
	static bool IsKeyInputRelease(int key);
};