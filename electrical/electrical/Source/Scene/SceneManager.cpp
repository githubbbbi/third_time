#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
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

	// �V�[���J��
	switch ( scene )
	{
		case e_TITLE:
			scene = nowScene->GetNextScene();
			break;

		case e_INITIALIZE:
			// ������������̓Q�[��
			nowScene.reset(new SceneGame);
			nowScene->Initialize();
			scene = e_GAME;
			break;

		case e_GAME:
			scene = nowScene->GetNextScene();
			break;

		case e_GAMEOVER:
			// �^�C�g���ɖ߂�
			//scene = nowScene->GetNextScene();
			break;

		case e_ENDING:
			//nowScene.reset(new SceneTitle);
			//scene = nowScene->GetNextScene();
			break;

		default:
			break;
	}

	// �V�[���𐶐�
	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneTitle);
			break;

		case e_GAME:
			// �Q�[���V�[���̓V�[���J�ڂ̏������V�[���ōs���Ă���̂�
			// �����ł͍s��Ȃ�
			break;

		case e_GAMEOVER:
			nowScene.reset(new SceneGameOver);
			break;

		case e_ENDING:
			//nowScene.reset(new SceneEnding);
			break;

		default:
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