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
	static int presstime[256] = { 0 };
	static int prevkey[256] = { 0 };

	// �L�[���͂����ꂽ�����瑝��
	presstime[key]++;

	// �L�[�������ꂽ�u�Ԃ̏ꍇ
	if (!prevkey[key] && IsKeyInputNow(key))
	{
		// �J�E���g�ϐ�
		static int i = 0;

		// �J�E���g�𑝂₷
		i++;

		// i��2�̏ꍇ
		if (i == 2)
		{
			// 2��ڂ̃L�[���͂�0.24�b��菬�����ꍇ
			if (presstime[key] <= 12)
			{
				// �J�E���g��0�ɃZ�b�g
				i = 0;

				// presstime[]���O�ɂ��Ă���
				presstime[key] = 0;

				return true;
			}
			else
			{
				i = 0;

				//presstime[]���O�ɂ��Ă���
				presstime[key] = 0;

				return false;
			}
		}
	}

	// ���̃t���[���̃L�[���͂�ۑ����āA��̃L�[���͔���̂Ƃ��g��
	prevkey[key] = IsKeyInputNow(key);

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