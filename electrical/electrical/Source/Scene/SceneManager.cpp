#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"
#include "../Resource/Graphic.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	// �摜�ǂݍ���
	Graphic::GetInstance()->Load();

	// BGM�ǂݍ���
	Sound_BGM::GetInstance()->Load();

	// SE�ǂݍ���
	Sound_SE::GetInstance()->Load();

	// �}�X�N�Z�b�g
	Mask::SetMask();

	isSCPossible = false;
}

SceneManager::~SceneManager()
{
	// delete
	nowScene.reset();
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

	// �g��\�t���O
	static bool isScaleUpPossible = false;

	// �ŏ��̎��g��\
	if ( Mask::IsExRateMin() )
	{
		isScaleUpPossible = true;
	}

	if ( !isScaleUpPossible )
	{
		return false;
	}

	// �}�X�N�̊g��I��
	if ( Mask::MaskScaleUp() )
	{
		// �V�[���J�ډ\
		isSCPossible = true;
		isScaleUpPossible = false;
		return true;
	}

	return false;
}

// �t�F�[�h�A�E�g
bool SceneManager::FadeOut()
{
	// �V�[���J�ڒ��ȊO�Ńt�F�[�h�A�E�g�͍s��Ȃ�
	if ( !nowScene->GetIsSceneChange() )
	{
		return false;
	}

	// �k���\�t���O
	static bool isScaleDownPossible = false;

	// �ő�̎��k���\
	if ( Mask::IsExRateMax() )
	{
		isScaleDownPossible = true;
	}

	if ( !isScaleDownPossible )
	{
		return false;
	}

	// �}�X�N�̏k���I��
	if ( Mask::MaskScaleDown() )
	{
		// �V�[���J�ڕs�\
		isSCPossible = false;
		isScaleDownPossible = false;
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

	// ���݂̃V�[���Ǝ��̃V�[���������̏ꍇ
	if ( scene == nowScene->GetNextScene() )
	{
		// �����������݂̂��s��
		nowScene->Initialize();
		return;
	}

	// �V�[���J��
	scene = nowScene->GetNextScene();

	// �J�ڌ�̃V�[���𐶐����������������s��(�����ɑJ�ڑO�̃V�[���̍폜���s��)
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
	nowScene->Update(isSCPossible);

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
	Mask::PostMask();
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