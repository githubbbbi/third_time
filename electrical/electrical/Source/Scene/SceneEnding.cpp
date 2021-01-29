#include "DxLib.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"

SceneEnding::SceneEnding()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
}

// ����������
void SceneEnding::Initialize()
{
	isSceneChange = false;
}

// �V�[���J��
void SceneEnding::SceneChange(bool isSCPossible)
{
	// �V�[���J�ڂ��\
	if ( !isSCPossible )
	{
		return;
	}

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
void SceneEnding::Update(bool isSCPossible)
{
	SceneChange(isSCPossible);
	GameEnd();
}

// �`�揈��
void SceneEnding::Draw()
{
	DrawRotaGraph(x, y, 2.0, 0.0,
				  Graphic::GetInstance()->GetEnding(), true);
}