#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"
#include "../Background/Background.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

SceneTitle::SceneTitle()
{
	ui = new UI_Title;
	GetGraphSize(Graphic::GetInstance()->GetTitle(), &width, &height);
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2 - height / 2;
}

SceneTitle::~SceneTitle()
{
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		delete lightnings[i];
		lightnings.erase(lightnings.begin() + i);
	}

	delete ui;
}

// ����������
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ���C�g�j���O�X�V����
void SceneTitle::UpdateLightning()
{
	const int wallX1 = x - width / 2;
	const int wallY1 = y - height / 2;
	const int wallX2 = x + width / 2;
	const int wallY2 = y + height / 2;

	// �ő吶����50��
	if ( lightnings.size() <= 50 )
	{
		// 1�t���[��3��
		for ( int i = 0; i < 3; i++ )
		{
			lightnings.push_back(new Effect_Lightning(wallX1, wallY1, wallX2, wallY2));
		}
	}

	// �X�V
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Update();
	}

	// ����
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		if ( lightnings[i]->IsLengthOver() )
		{
			delete lightnings[i];
			lightnings.erase(lightnings.begin() + i);
		}
	}
}

// ���C�g�j���O�`�揈��
void SceneTitle::DrawLightning()
{
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}
}

// �V�[���J��
void SceneTitle::SceneChange(bool isSCPossible)
{
	// �V�[���J�ڂ��\
	if ( !isSCPossible )
	{
		return;
	}

	// ���C���Q�[���֑J��
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_GAME;

		// BGM��~
		Sound_BGM::GetInstance()->StopBGM(e_TITLE_BGM);

		// SE�Đ�
		if ( !isSceneChange )
		{
			Sound_SE::GetInstance()->PlaySE(e_GAME_START_SE, true);
		}

		isSceneChange = true;
	}
}

// �Q�[���I��
void SceneTitle::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// �X�V����
void SceneTitle::Update(bool isSCPossible)
{
	// BGM�Đ�
	if ( !isSceneChange )
	{
		Sound_BGM::GetInstance()->PlayBGM(e_TITLE_BGM);
	}

	UpdateLightning();

	// �^�C�g��UI �V�[���J�ڎ��ɓ_�ŁA�����łȂ���Ζ���
	ui->Update(!isSceneChange, isSceneChange);
	SceneChange(isSCPossible);
	GameEnd();
}

// �`�揈��
void SceneTitle::Draw()
{
	// �w�i
	Background back;
	back.Draw(0.0f, 0.0f,0);

	DrawLightning();
	DrawRotaGraph(x, y, 1.0, 0.0,
				  Graphic::GetInstance()->GetTitle(), true);

	ui->Draw();
}