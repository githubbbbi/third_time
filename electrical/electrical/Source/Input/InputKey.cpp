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
	static int pressTime[256] = { 0 };
	static int prevKey[256] = { 0 };

	// �L�[���͂����ꂽ�����瑝��
	pressTime[key]++;

	// �L�[�������ꂽ�u�Ԃ̏ꍇ
	if ( !prevKey[key] && IsKeyInputNow(key) )
	{
		// �J�E���g�ϐ�
		static int i = 0;

		// �J�E���g�𑝂₷
		i++;

		// i��2�̏ꍇ
		if ( i == 2 )
		{
			// 2��ڂ̃L�[���͂�0.3�b��菬�����ꍇ
			if ( pressTime[key] <= 15 )
			{
				// �J�E���g��0�ɃZ�b�g
				i = 0;

				// pressTime[]���O�ɂ��Ă���
				pressTime[key] = 0;

				return true;
			}
			else
			{
				i = 0;

				//presstTime[]���O�ɂ��Ă���
				pressTime[key] = 0;

				return false;
			}
		}
	}

	// ���̃t���[���̃L�[���͂�ۑ����āA��̃L�[���͔���̂Ƃ��g��
	prevKey[key] = IsKeyInputNow(key);

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