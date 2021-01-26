#include "DxLib.h"
#include "SceneGameOver.h"
#include "../Input/InputManager.h"

SceneGameOver::SceneGameOver()
{
}

// ����������
void SceneGameOver::Initialize()
{
	isSceneChange = false;
}

// �V�[���J��
void SceneGameOver::SceneChange()
{
	// �^�C�g���֑J��
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_TITLE;
		isSceneChange = true;
	}
}

// �Q�[���I��
void SceneGameOver::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneGameOver::Update()
{
	SceneChange();
	GameEnd();
}

// �`�揈��
void SceneGameOver::Draw()
{
	DrawString(500, 100, "GAMEOVER", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}