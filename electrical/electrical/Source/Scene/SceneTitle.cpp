#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneTitle::SceneTitle()
{
}

// ����������
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ���C�e�B���O�X�V����
void SceneTitle::LightingUpdate()
{

}

// ���C�e�B���O�`�揈��
void SceneTitle::LightingDraw()
{

}

// �V�[���J��
void SceneTitle::SceneChange()
{
	// ���C���Q�[���֑J��
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_GAME;
		isSceneChange = true;
	}
}

// �Q�[���I��
void SceneTitle::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneTitle::Update()
{
	LightingUpdate();
	SceneChange();
	GameEnd();
}

// �`�揈��
void SceneTitle::Draw()
{
	LightingDraw();
	DrawString(500, 100, "TITLE", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}