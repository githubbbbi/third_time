#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	// �}�X�N�Z�b�g
	Mask::SetMask();
}

// ����������
void SceneManager::Initialize()
{
	nowScene->Initialize();
}

// �X�V����
void SceneManager::Update()
{
	// ����
	InputManager::Update();

	// ���݂̃V�[��
	nowScene->Update();

	// �V�[���J��
	SceneChange();
}

// �`�揈��
void SceneManager::Draw()
{
	// �}�X�N�̕`��
	Mask::DrawMask();

	// ���݂̃V�[��
	nowScene->Draw();

	// �}�X�N�̌㏈��
	Mask::LoopMask();
}

// �V�[���J��
void SceneManager::SceneChange()
{
	if ( !nowScene->GetIsSceneChange() )
	{
		return;
	}

	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneGame);
			scene = e_GAME;
			break;

		case e_GAME:
			nowScene.reset(new SceneTitle);
			scene = e_TITLE;
			break;

		case e_ENDING:
			//nowScene.reset(new SceneTitle);
			//scene = e_TITLE;
			break;
	}
}

// �Q�[���I��
bool SceneManager::GetIsGameEnd()
{
	return nowScene->GetIsGameEnd();
}