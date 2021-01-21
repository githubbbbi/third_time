#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Input/InputManager.h"
#include "../Background/Background.h"

// �R���X�g���N�^
SceneGame::SceneGame()
{
	// �L�����N�^�[
	charaManager = new Chara_Manager;

	// �X�e�[�W
	stage = new Stage();

	// �G�t�F�N�g
	effects = new EffectManager();

	scrollX = 0;
	scrollY = 0;

	screenX = 0;
	screenY = 0;
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	delete charaManager;
	delete stage;
	delete effects;
}

// ����������
void SceneGame::Initialize()
{
	// �X�e�[�W
	if ( !stage->Initialize() )
	{
		isGameEnd = true;
	}

	// �L�����N�^�[
	charaManager->Initialize();

	isSceneChange = false;
}

// �X�N���[�����W�����߂�
void SceneGame::Screen()
{
	screenX = scrollX + WIN_WIDTH / 2;
	screenY = scrollY + WIN_HEIGHT / 2;
}

// �G�t�F�N�g�Ǘ�
void SceneGame::LocalEffectManager()
{
	// �L�����N�^�[�̎��S�G�t�F�N�g
	if ( charaManager->GetIsCharaDeath() )
	{
		// �V�F�C�N
		effects->Shake();

		// ����
		effects->Explosion(charaManager->GetExplosionPosX(),
						   charaManager->GetExplosionPosY());
	}

	// �G�t�F�N�g
	effects->Update();
}

// �V�[���J��
void SceneGame::SceneChange()
{
	// �e�X�g�p
	/*if ( InputManager::IsInputRelease(e_START) )
	{
		isSceneChange = true;
	}*/
}

// �Q�[���I��
void SceneGame::GameEnd()
{
	// �e�X�g�p
	if ( InputManager::IsInputRelease(e_PAUSE) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneGame::Update()
{
	// �X�N���[�����W�����߂�
	Screen();

	// �G�t�F�N�g
	LocalEffectManager();

	// �X�N���[��
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// �X�e�[�W
	stage->Update();

	// �L�����N�^�[
	charaManager->Update(screenX, screenY);

	// �V�[���J��
	SceneChange();

	// �Q�[���I��
	GameEnd();
}

// �`�揈��
void SceneGame::Draw()
{
	// �w�i
	Background back;
	back.Draw(effects->GetShakeX(), effects->GetShakeY());

	// �X�e�[�W
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(),
				scrollX, scrollY, screenX, screenY);

	// �L�����N�^�[
	charaManager->Draw(effects->GetShakeX(),
					   effects->GetShakeY(), scrollX, scrollY);

	// �G�t�F�N�g
	effects->Draw(scrollX, scrollY);

	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 255, 255), "%d,%d", screenX, screenY);
	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 20, GetColor(255, 255, 255), "%d,%d", scrollX, scrollY);
}

// �I������
void SceneGame::Finalize()
{

}