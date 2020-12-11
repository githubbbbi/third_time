#include "DxLib.h"
#include "InputKey.h"

// �ϐ�������
char InputKey::keys[] = { 0 };
char InputKey::oldKeys[] = { 0 };

int InputKey::inputFrame = 0;

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

//// �A�ł��ꂽ�ꍇTRUE
//bool InputKey::IsKeyInputBarrage(int key)
//{
//	static int presstime[2] = { 0 };
//	static int prevkey = 0;
//	if (!prevkey && CheckHitKey(key))//�L�[�������ꂽ�u�ԂȂ�
//	{
//		static int i = 0;//�J�E���g�ϐ�
//		static int j = 0;//�J�E���g�ϐ�
//		presstime[i] = GetTickCount64();//���̎��Ԃ��m�肽���i�~���b�P�ʂ�)
//		++i;//�J�E���g����
//		if (i == 2)//i��2�Ȃ�
//		{
//			if ((long long)presstime[1] - presstime[0] <= 0.35 * 1000)//�Q�̎��ԍ���0.35�b��菬�������
//			{
//				i = 0;//i��0�ɂ���
//				presstime[0] = 0;//presstime[]���Q�Ƃ��O�ɂ��Ă���
//				presstime[1] = 0;
//				return 1;//1��Ԃ�
//			}
//			else {
//				i = 0;//i��0�ɂ���
//				presstime[0] = 0;//presstime[]���Q�Ƃ��O�ɂ��Ă���
//				presstime[1] = 0;
//				return 0;	//0��Ԃ�
//			}
//		}
//	}
//
//	prevkey = CheckHitKey(key);//���̃t���[���̃L�[���͂�ۑ����āA
//							//��̃L�[���͔���̂Ƃ��g��
//	return 0;
//}
