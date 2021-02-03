#include "InputKey.h"

// �ϐ�������
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

// �X�V����
void InputKey::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for ( int i = 0; i < 256; i++ )
	{
		oldKeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

// ������Ă���ꍇTRUE
bool InputKey::IsKeyInputNow(int key)
{
	if ( keys[key] )
	{
		return true;
	}

	return false;
}

// �O�t���[����������Ă��Ȃ���Ԃ��牟���ꂽ�ꍇTRUE
bool InputKey::IsKeyInputTrigger(int key)
{
	if ( !oldKeys[key] && keys[key] )
	{
		return true;
	}

	return false;
}

// ������Ă��ė����ꂽ�ꍇTRUE
bool InputKey::IsKeyInputRelease(int key)
{
	if ( oldKeys[key] && !keys[key] )
	{
		return true;
	}

	return false;
}

// �A�ł��ꂽ�ꍇTRUE
bool InputKey::IsKeyInputBarrage(int key)
{
	// ���������Ԃ��v�����邽�߂̕ϐ�
	static int pushTime[256] = { 0 };

	// �O�̃t���[���𔻒肷�邽�߂̕ϐ�
	static int oldFrame[256] = { 0 };

	// �ĂуL�[���͂�����܂ő҂Ă�t���[����
	const int waitFrame = 15;

	if ( !oldFrame[key] && keys[key] )
	{
		// �������u�ԂȂ�
		if ( pushTime[key] != 0 )
		{
			return true;
		}
		else
		{
			pushTime[key] = waitFrame;
		}
	}

	oldFrame[key] = keys[key];

	// ���������Ԃ�0����Ȃ��Ȃ�
	if ( pushTime[key] != 0 )
	{
		// ���������Ԃ��f�N�������g
		pushTime[key]--;
	}

	return false;
}

// ������Ă��Ȃ��ꍇ
bool InputKey::IsKeyInputNot(int key)
{
	if ( !keys[key] )
	{
		return true;
	}

	return false;
}