#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Input/InputManager.h"
#include "../Background/Background.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

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
	displaceX = 0.0f;
	displaceY = 0.0f;
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

	// UI
	ui->Initialize();

	scrollX = ((int)characters->GetScrollCenterX() / WIN_WIDTH) * WIN_WIDTH;
	scrollY = ((int)characters->GetScrollCenterY() / WIN_HEIGHT) * WIN_HEIGHT;
	screenX = WIN_WIDTH / 2;
	screenY = WIN_HEIGHT / 2;
	displaceX = 0.0f;
	displaceY = 0.0f;
	isScroll = false;
	isDrawUIMM = false;

	r = g = b = 255.0f;
	h = s = v = 255.0f;

	isSceneChange = false;
}

// �v���C���[�����i�s:-1,�E�i�s:1��Ԃ�
int SceneGame::PlayerMoveLR()
{
	float moveX = characters->GetPlayerMoveX();
	if ( moveX > 0.0f )
	{
		return 1;
	}
	else if ( moveX < 0.0f )
	{
		return -1;
	}

	return 0;
}

// �v���C���[����i�s:-1,���i�s:1��Ԃ�
int SceneGame::PlayerMoveUD()
{
	float moveY = characters->GetPlayerMoveY();
	if ( moveY > 0.0f )
	{
		return 1;
	}
	else if ( moveY < 0.0f )
	{
		return -1;
	}

	return 0;
}

// �X�N���[�����W�����߂�
void SceneGame::Screen()
{
	screenX = scrollX + WIN_WIDTH / 2;
	screenY = scrollY + WIN_HEIGHT / 2;
}

// �G�t�F�N�g�Ǘ�
void SceneGame::MyEffectManager()
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

	// �N���A���̃G�t�F�N�g
	if ( characters->GetPlayerIsGoal() )
	{
		effects->Clear(characters->GetPlayerX(),
					   characters->GetPlayerY());
	}

	// �G�t�F�N�g
	effects->Update();
}

// UI�Ǘ�
void SceneGame::MyUIManager()
{
	// �X�V����
	ui->Update(characters->GetPlayerHp(),
			   characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(),
			   characters->GetPlayerMaxBattery(), isDrawUIMM);

	// ����ꗗ�\�����łȂ�
	if ( !isDrawUIMM )
	{
		h = 0.0f;
		s = 0.0f;
		v = 255.0f;
	}
	// ����ꗗ�\����
	else
	{
		h = 0.0f;
		s = 0.0f;
		v = 64.0f;
	}

	//  READY�̏ꍇ�͏������s��Ȃ�
	if ( ui->GetIsReady() )
	{
		return;
	}

	// �w���v(����ꗗ��\��)
	if ( !isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE�Đ�
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = true;
		return;
	}

	// �w���v�����
	if ( isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE�Đ�
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = false;
		return;
	}
}

// �V�[���J��
void SceneGame::SceneChange(bool isSCPossible)
{
	// �V�[���J�ڂ��\
	if ( !isSCPossible )
	{
		return;
	}

	// �v���C���[�����S������������
	if ( !characters->GetPlayerIsAlive() )
	{
		// BGM��~
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);
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
		// BGM��~
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);

		// ���ׂĂ�SE��~
		if ( !isSceneChange )
		{
			Sound_SE::GetInstance()->StopAllSE();
		}

		// SE(�W���O��)�Đ�
		Sound_SE::GetInstance()->PlaySE(e_STAGE_CLEAR_SE, true);
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
void SceneGame::Update(bool isSCPossible)
{
	// BGM�Đ�
	if ( !isSceneChange )
	{
		Sound_BGM::GetInstance()->PlayBGM(e_GAME_BGM);
	}

	// ����ꗗ�\�����͍X�V�������s��Ȃ�
	if ( !isDrawUIMM )
	{
		// SE�Đ�
		if ( isScroll )
		{
			Sound_SE::GetInstance()->PlaySE(e_SCROLL_SE, true);
		}

		// �X�N���[��
		Utility::Scroll((int)characters->GetScrollCenterX() + (int)displaceX +
						((int)(displaceX / (screenX / (WIN_WIDTH / 2))) * PlayerMoveLR()),
						(int)characters->GetScrollCenterY() + (int)displaceY +
						((int)(displaceY / (screenY / (WIN_HEIGHT / 2))) * PlayerMoveUD()),
						&scrollX, &scrollY, (int)displaceX, (int)displaceY, &isScroll);

		// �G�t�F�N�g
		MyEffectManager();

		// �X�N���[�����܂���READY�̏ꍇ�͍X�V�������s��Ȃ�
		if ( !isScroll && !ui->GetIsReady() )
		{
			// �L�����N�^�[
			characters->Update(screenX, screenY);
		}
	}

	// �X�N���[�����W�����߂�
	Screen();

	// �I�u�W�F�N�g���X�N���[���̒��S�ɂ��炷
	Utility::DisplaceObjScrnCntr(screenX, screenY,
								 &displaceX, &displaceY);

	// �L�����N�^�[��displaceX,displaceY��ݒ�
	characters->SetDisplaceX((int)displaceX);
	characters->SetDisplaceY((int)displaceY);

	// UI
	MyUIManager();

	// HSV����RGB�֕ϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);

	// �V�[���J��
	SceneChange(isSCPossible);

	// �Q�[���I��
	GameEnd();
}

// �`�揈��
void SceneGame::Draw()
{
	SetDrawBright((int)r, (int)g, (int)b);
	// �w�i
	Background back;
	back.Draw(effects->GetShakeX(), effects->GetShakeY(), 1);

	// �X�e�[�W
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(),
				scrollX, scrollY,
				screenX, screenY,
				(int)displaceX, (int)displaceY);

	// �L�����N�^�[
	characters->Draw(effects->GetShakeX(),
					 effects->GetShakeY(),
					 scrollX, scrollY);

	// �G�t�F�N�g
	effects->Draw(scrollX, scrollY,
				  (int)displaceX, (int)displaceY);

	// UI
	ui->Draw(characters->GetPlayerHp(),
			 characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(),
			 characters->GetPlayerMaxBattery(), isDrawUIMM);

	SetDrawBright(255, 255, 255);
}