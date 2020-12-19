#include "InputKey.h"

// �ϐ�������
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

float InputKey::frameCount[] = { 0.0f };

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
	static long long int presstime[2][2] = { 0 };
	static int prevkey[2] = { 0 };

	if ( key == e_KEY_LEFT )
	{
		// �L�[�������ꂽ�u�Ԃ̏ꍇ
		if ( !prevkey[0] && IsKeyInputNow(key) )
		{
			static int i = 0;	// �J�E���g�ϐ�

			// ���̎��Ԃ��m�肽���i�~���b�P�ʂ�)
			presstime[0][i] = GetTickCount64();
			++i;

			// i��2�̏ꍇ
			if ( i == 2 )
			{
				// �Q�̎��ԍ���0.35�b��菬�����ꍇ
				if ( presstime[0][1] - presstime[0][0] <= 0.25 * 1000 )
				{
					i = 0;

					// presstime[]���Q�Ƃ��O�ɂ��Ă���
					presstime[0][0] = 0;
					presstime[0][1] = 0;

					return true;
				}
				else
				{
					i = 0;

					//presstime[]���Q�Ƃ��O�ɂ��Ă���
					presstime[0][0] = 0;
					presstime[0][1] = 0;

					return false;
				}
			}
		}
		// ���̃t���[���̃L�[���͂�ۑ����āA��̃L�[���͔���̂Ƃ��g��
		prevkey[0] = IsKeyInputNow(key);
	}
	else if ( key == e_KEY_RIGHT )
	{
		// �L�[�������ꂽ�u�Ԃ̏ꍇ
		if ( !prevkey[1] && IsKeyInputNow(key) )
		{
			static int j = 0;	// �J�E���g�ϐ�

			// ���̎��Ԃ��m�肽���i�~���b�P�ʂ�)
			presstime[1][j] = GetTickCount64();
			++j;

			// i��2�̏ꍇ
			if ( j == 2 )
			{
				// �Q�̎��ԍ���0.35�b��菬�����ꍇ
				if ( presstime[1][1] - presstime[1][0] <= 0.25 * 1000 )
				{
					j = 0;

					// presstime[]���Q�Ƃ��O�ɂ��Ă���
					presstime[1][0] = 0;
					presstime[1][1] = 0;

					return true;
				}
				else
				{
					j = 0;

					//presstime[]���Q�Ƃ��O�ɂ��Ă���
					presstime[1][0] = 0;
					presstime[1][1] = 0;

					return false;
				}
			}
		}
		// ���̃t���[���̃L�[���͂�ۑ����āA��̃L�[���͔���̂Ƃ��g��
		prevkey[1] = IsKeyInputNow(key);
	}


	return false;
}

// frameCount��Ԃ�
float InputKey::GetInputFrame(int key)
{
	return frameCount[key];
}

// frameCount���C���N�������g����
void InputKey::IncrementFrame(int key)
{
	frameCount[key]++;
}

// frameCount�����Z�b�g����
void InputKey::ResetFrame(int key)
{
	frameCount[key] = 0;
}
