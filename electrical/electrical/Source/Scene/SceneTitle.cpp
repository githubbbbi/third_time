#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

// ����������
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ���C�g�j���O�X�V����
void SceneTitle::LightningUpdate()
{
	// �ő吶����50��
	int wallX1 = 170;
	int wallY1 = 150;
	int wallX2 = 760;
	int wallY2 = 250;
	if ( lightnings.size() <= 50 )
	{
		// 1�t���[��3��
		for ( int i = 0; i < 3; i++ )
		{
			lightnings.push_back(new Effect_Lightning(wallX1, wallY1, wallX2, wallY2));
		}
	}

	// �X�V
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Update();
	}

	// ����
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		if ( lightnings[i]->IsLengthOver() )
		{
			delete lightnings[i];
			lightnings.erase(lightnings.begin() + i);
		}
	}
}

// ���C�g�j���O�`�揈��
void SceneTitle::LightningDraw()
{
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}
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
	LightningUpdate();
	SceneChange();
	GameEnd();
}

// �`�揈��
void SceneTitle::Draw()
{
	LightningDraw();
	//DrawString(500, 100, "TITLE", GetColor(255, 255, 255));
	//DrawString(500, 200, "space", GetColor(255, 255, 255));
}