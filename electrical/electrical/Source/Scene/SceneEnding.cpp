#include "DxLib.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneEnding::SceneEnding()
{
}

// ����������
void SceneEnding::Initialize()
{
	isSceneChange = false;
}

// �V�[���J��
void SceneEnding::SceneChange()
{
	// �^�C�g���֑J��
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_TITLE;
		isSceneChange = true;
	}
}

// �Q�[���I��
void SceneEnding::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneEnding::Update()
{
	SceneChange();
	GameEnd();
}

// �`�揈��
void SceneEnding::Draw()
{
	DrawString(500, 100, "ENDING", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}