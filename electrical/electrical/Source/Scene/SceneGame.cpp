#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Utility/Frame.h"
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

	// ���^�[�{�b�N�X
	for ( int i = 0; i < 4; i++ )
	{
		letterBox[i] = { 0, 0, 0, 0,
						 0.0f, 0.0f, 0.0f,
						 0.0f, 0.0f, 0.0f };
	}

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

// �X�N���[�����W�̏���������
void SceneGame::InitScreenPos()
{
	// �X�N���[���̒��S�ƂȂ�L�����N�^�[�̍��W
	int charaX = (int)characters->GetScrollCenterX();
	int charaY = (int)characters->GetScrollCenterY();

	// ���ݕ`�悳��Ă���X�N���[���̒��S���W
	screenX = (charaX / ROOM_SIZE_X) * WIN_WIDTH + WIN_WIDTH / 2;
	screenY = (charaY / ROOM_SIZE_Y) * WIN_HEIGHT + WIN_HEIGHT / 2;
}

// �X�N���[�����W�̏���������
void SceneGame::InitScrollPos()
{
	// �X�N���[�����W�̏���������
	InitScreenPos();

	// �X�N���[����
	scrollX = screenX - WIN_WIDTH / 2;
	scrollY = screenY - WIN_HEIGHT / 2;
}

// ���^�[�{�b�N�X�̏���������
void SceneGame::InitLetterBox()
{
	// �����c�̃��^�[�{�b�N�X
	letterBox[0].x1 = 0;
	letterBox[0].x2 = letterBox[0].x1 + DISPLACE_X;
	letterBox[0].y1 = 0;
	letterBox[0].y2 = WIN_HEIGHT;

	// �E���c�̃��^�[�{�b�N�X
	letterBox[1].x1 = WIN_WIDTH - DISPLACE_X;
	letterBox[1].x2 = letterBox[1].x1 + DISPLACE_X;
	letterBox[1].y1 = 0;
	letterBox[1].y2 = WIN_HEIGHT;

	// �㑤���̃��^�[�{�b�N�X
	letterBox[2].x1 = 0;
	letterBox[2].x2 = WIN_WIDTH;
	letterBox[2].y1 = 0;
	letterBox[2].y2 = letterBox[2].y1 + DISPLACE_Y;

	// �������̃��^�[�{�b�N�X
	letterBox[3].x1 = 0;
	letterBox[3].x2 = WIN_WIDTH;
	letterBox[3].y1 = WIN_HEIGHT - DISPLACE_Y;
	letterBox[3].y2 = letterBox[3].y1 + DISPLACE_Y;

	// �F��ݒ�
	for ( int i = 0; i < 4; i++ )
	{
		letterBox[i].h = 198.0f;
		letterBox[i].s = 84.0f;
		//letterBox[i].v = 117.0f;
		letterBox[i].v = 0.0f;
		// hsv����rgb�ɕϊ�
		Utility::ConvertHSVtoRGB(&letterBox[i].r, &letterBox[i].g, &letterBox[i].b,
								 letterBox[i].h, letterBox[i].s, letterBox[i].v);
	}
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

	// �X�N���[�����W�̏���������
	InitScrollPos();

	// �I�u�W�F�N�g���X�N���[���̒��S�ɂ��炷
	Utility::DisplaceObjScrnCntr(screenX, screenY,
								 &displaceX, &displaceY);

	// ���^�[�{�b�N�X�̏���������
	InitLetterBox();

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
void SceneGame::CalcScreenPos()
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

// ���^�[�{�b�N�X�̕`�揈��
void SceneGame::DrawLetterBox()
{
	for ( int i = 0; i < 4; i++ )
	{
		int color = GetColor((int)letterBox[i].r,
							 (int)letterBox[i].g,
							 (int)letterBox[i].b);
		DrawBox(letterBox[i].x1, letterBox[i].y1,
				letterBox[i].x2, letterBox[i].y2,
				color, true);
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
		Utility::Scroll((int)characters->GetScrollCenterX() +
						(int)displaceX + (DISPLACE_X * PlayerMoveLR()),
						(int)characters->GetScrollCenterY() +
						(int)displaceY + (DISPLACE_Y * PlayerMoveUD()),
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
	CalcScreenPos();

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
	SetDrawBright(255, 255, 255);

	// ���^�[�{�b�N�X
	DrawLetterBox();

	// UI
	ui->Draw(characters->GetPlayerHp(),
			 characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(),
			 characters->GetPlayerMaxBattery(), isDrawUIMM);

	// �g
	Frame frame;
	frame.Draw();
}