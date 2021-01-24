#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"

SceneTitle::SceneTitle()
{
}

// ����������
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// �V�[���J��
void SceneTitle::SceneChange()
{
	// �����������֑J��
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_INITIALIZE;
		isSceneChange = true;
	}
}

// �Q�[���I��
void SceneTitle::GameEnd()
{
	if ( InputManager::IsInputRelease(e_PAUSE) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneTitle::Update()
{
	SceneChange();
	GameEnd();
}

// �`�揈��
void SceneTitle::Draw()
{
	DrawString(500, 100, "TITLE", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}