#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
#include "SceneEnding.h"
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

// �t�F�[�h�C��
bool SceneManager::FadeIn()
{
	// �V�[���J�ڒ��ɂ̓t�F�[�h�C���͍s��Ȃ�
	if ( nowScene->GetIsSceneChange() )
	{
		return false;
	}

	// �}�X�N�̊g��I��
	if ( Mask::MaskScaleUp() )
	{
		return true;
	}

	return false;
}

// �t�F�[�h�A�E�g
bool SceneManager::FadeOut()
{
	if ( !nowScene->GetIsSceneChange() )
	{
		return false;
	}

	// �}�X�N�̏k���I��
	if ( Mask::MaskScaleDown() )
	{
		return true;
	}

	return false;
}

// �V�[���J��
void SceneManager::SceneChange()
{
	// �t�F�[�h�A�E�g��ɃV�[���J�ڂ��s��
	if ( !FadeOut() )
	{
		return;
	}

	// �V�[���J��
	switch ( scene )
	{
		case e_TITLE:
			scene = nowScene->GetNextScene();
			break;

		case e_GAME:
			scene = nowScene->GetNextScene();
			break;

		case e_GAMEOVER:
			scene = nowScene->GetNextScene();
			break;

		case e_ENDING:
			scene = nowScene->GetNextScene();
			break;

		default:
			break;
	}

	// �J�ڌ�̃V�[���𐶐����������������s��
	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneTitle);
			nowScene->Initialize();
			break;

		case e_GAME:
			nowScene.reset(new SceneGame);
			nowScene->Initialize();
			break;

		case e_GAMEOVER:
			nowScene.reset(new SceneGameOver);
			nowScene->Initialize();
			break;

		case e_ENDING:
			nowScene.reset(new SceneEnding);
			nowScene->Initialize();
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

	// �t�F�[�h�C��
	FadeIn();

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