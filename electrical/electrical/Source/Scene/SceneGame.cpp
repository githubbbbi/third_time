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
	characters = new Chara_Manager;

	// �X�e�[�W
	stage = new Stage;

	// �G�t�F�N�g
	effects = new EffectManager;

	// UI
	ui = new UI_Manager;

	scrollX = 0;
	scrollY = 0;

	screenX = 0;
	screenY = 0;
}

// �f�X�g���N�^
SceneGame::~SceneGame()
{
	delete characters;
	delete stage;
	delete effects;
	delete ui;
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
	if ( !characters->Initialize() )
	{
		isGameEnd = true;
	}

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
	if ( characters->GetIsCharaDeath() )
	{
		// �V�F�C�N
		effects->Shake();

		// ����
		effects->Explosion(characters->GetExplosionPosX(),
						   characters->GetExplosionPosY());
	}

	// �G�t�F�N�g
	effects->Update();
}

// �V�[���J��
void SceneGame::SceneChange()
{
	// �v���C���[�����S���c�@�����聨����������
	if ( !characters->GetPlayerIsAlive() &&
		characters->GetPlayerRemainingNum() > 0 )
	{
		nextScene = e_GAME;
		isSceneChange = true;
		return;
	}

	// �v���C���[�����S���c�@���Ȃ����Q�[���I�[�o�[
	if ( !characters->GetPlayerIsAlive() &&
		characters->GetPlayerRemainingNum() <= 0 )
	{
		nextScene = e_GAMEOVER;
		isSceneChange = true;
		return;
	}

	// �v���C���[���S�[�����G���f�B���O
	if ( characters->GetPlayerIsGoal() )
	{
		nextScene = e_GAME;// �e�X�g�p
		//nextScene = e_ENDING;
		isSceneChange = true;
		return;
	}
}

// �Q�[���I��
void SceneGame::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
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
	Utility::Scroll((int)characters->GetScrollCenterX(),
					(int)characters->GetScrollCenterY(), &scrollX, &scrollY);

	// �L�����N�^�[
	characters->Update(screenX, screenY);

	// UI
	ui->Update(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(), characters->GetPlayerMaxBattery());

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
	characters->Draw(effects->GetShakeX(),
					 effects->GetShakeY(), scrollX, scrollY);

	// �G�t�F�N�g
	effects->Draw(scrollX, scrollY);

	// UI
	ui->Draw(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(), characters->GetPlayerMaxBattery());

	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 255, 255), "%d,%d", screenX, screenY);
	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 20, GetColor(255, 255, 255), "%d,%d", scrollX, scrollY);
}

// �I������
void SceneGame::Finalize()
{

}