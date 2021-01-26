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
	// �ő吶����50��(wall�n�͗����˗p�̃^�C�g������̎l�p�̒l)

	//if ( lightnings.size() <= 50 )
	//{
	//	// 1�t���[��3��
	//	for ( int i = 0; i < 3; i++ )
	//	{
	//		lightnings.push_back(new Lightning(wallX, wallY, wallX2, wallY2));
	//	}
	//}

	//// �X�V�@������
	//for ( unsigned int i = 0; i < lightnings.size(); i++ )
	//{
	//	lightnings[i]->Initialize();
	//	lightnings[i]->Update();
	//}

	//// ����(is�t���ĂȂ��Ȃ���@���߂�j
	//for ( int i = lightnings.size() - 1; i >= 0; i-- )
	//{
	//	if ( lightnings[i]->LengthOver() )
	//	{
	//		delete lightnings[i];
	//		lightnings.erase(lightnings.begin() + i);
	//	}
	//}
}

// ���C�e�B���O�`�揈��
void SceneTitle::LightingDraw()
{
	// ��
	/*for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}*/
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