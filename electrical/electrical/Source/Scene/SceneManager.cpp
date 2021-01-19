#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"
#include "../Resource/Graphic.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	Graphic::GetInstance()->Load();

	// �}�X�N�Z�b�g
	Mask::SetMask();
}

// ����������
void SceneManager::Initialize()
{
	nowScene->Initialize();
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
			scene = e_INITIALIZE;
			break;

		case e_INITIALIZE:
			nowScene.reset(new SceneGame);
			scene = e_GAME;
			nowScene->Initialize();
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

// �I������
void SceneManager::Finalize()
{
	// �摜���
	Graphic::GetInstance()->Release();
}

// �Q�[���I��
bool SceneManager::GetIsGameEnd()
{
	return nowScene->GetIsGameEnd();
}