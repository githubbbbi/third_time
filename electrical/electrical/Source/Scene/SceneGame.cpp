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
	isScroll = false;
	isDrawUIMM = false;

	r = g = b = 255.0f;
	h = s = v = 255.0f;
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

// UI�Ǘ�
void SceneGame::LoaclUIManager()
{
	// �X�V����
	ui->Update(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);

	// ����ꗗ�\�����͌��̖��x��������
	if ( !isDrawUIMM )
	{
		h = 0.0f;
		s = 0.0f;
		v = 255.0f;
	}
	else
	{
		h = 0.0f;
		s = 0.0f;
		v = 64.0f;
	}

	// �w���v(����ꗗ��\��)
	if ( !isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		isDrawUIMM = true;
		return;
	}

	// �w���v�����
	if ( isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		isDrawUIMM = false;
		return;
	}
}

// �V�[���J��
void SceneGame::SceneChange()
{
	// �v���C���[�����S������������
	if ( !characters->GetPlayerIsAlive() )
	{
		nextScene = e_GAME;
		isSceneChange = true;
		return;
	}

	// �v���C���[���S�[�����G���f�B���O
	if ( characters->GetPlayerIsGoal() )
	{
		// ��莞�Ԍo��
		static int timer = 0;
		if ( timer++ < 30 )
		{
			return;
		}

		timer = 0;
		nextScene = e_ENDING;
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

	// ����ꗗ�\�����͍X�V�������s��Ȃ�
	if ( !isDrawUIMM )
	{
		// �X�N���[��
		Utility::Scroll((int)characters->GetScrollCenterX(),
						(int)characters->GetScrollCenterY(),
						&scrollX, &scrollY, &isScroll);

		// �G�t�F�N�g
		LocalEffectManager();

		// �X�N���[�����͍X�V�������s��Ȃ�
		if ( !isScroll )
		{
			// �L�����N�^�[
			characters->Update(screenX, screenY);

		}
	}

	// UI
	LoaclUIManager();

	// HSV����RGB�֕ϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);

	// �V�[���J��
	SceneChange();

	// �Q�[���I��
	GameEnd();
}

// �`�揈��
void SceneGame::Draw()
{
	SetDrawBright((int)r, (int)g, (int)b);
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
	SetDrawBright(255, 255, 255);

	// UI
	ui->Draw(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);
}

// �I������
void SceneGame::Finalize()
{

}