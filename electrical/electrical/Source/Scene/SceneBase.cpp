#include "SceneBase.h"

SceneBase::SceneBase()
{
	nextScene = e_NONE;
	isSceneChange = false;
	isGameEnd = false;
}

Scene SceneBase::GetNextScene()
{
	return nextScene;
}

// �V�[���J�ڂ���܂ł̎���
int SceneBase::SceneChangeTime()
{
	// �^�C�g�����Q�[���܂��̓Q�[�����Q�[��
	if ( nextScene == e_GAME )
	{
		return 120;
	}

	// �Q�[�����G���f�B���O
	if ( nextScene == e_ENDING )
	{
		return 210;
	}

	// �G���f�B���O���^�C�g��
	if ( nextScene == e_TITLE )
	{
		return 0;
	}

	return 0;
}

bool SceneBase::GetIsSceneChange()
{
	static int timer = 0;
	if ( !isSceneChange )
	{
		timer = 0;
		return false;
	}

	// ��莞�Ԍo�߂�TRUE��Ԃ�
	if ( timer++ < SceneChangeTime() )
	{
		return false;
	}

	return true;
}

bool SceneBase::GetIsGameEnd()
{
	return isGameEnd;
}