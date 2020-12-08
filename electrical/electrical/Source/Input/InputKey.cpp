#include "DxLib.h"
#include "InputKey.h"

// �ϐ�������
char InputKey::keys[] = { 0 };
char InputKey::oldkeys[] = { 0 };

// �X�V����
void InputKey::KeyUpdate()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for ( int i = 0; i < 256; i++ )
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
bool InputKey::IsKeyInputNow(int key)
{
	if ( oldkeys[key] == FALSE && keys[key] == TRUE )
	{
		return true;
	}

	return false;
}

// ������Ă��ė����ꂽ�ꍇTRUE
bool InputKey::IsKeyInputRelease(int key)
{
	if ( oldkeys[key] == TRUE && keys[key] == FALSE )
	{
		return true;
	}

	return false;
}