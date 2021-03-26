#include "DxLib.h"
#include <time.h>
#include "System.h"
#include "SettingDxLib.h"
#include "FrameRate.h"

// �R���X�g���N�^
System::System()
{
	scene = nullptr;
}

// �f�X�g���N�^
System::~System()
{
	delete scene;
}

// ����������
bool System::Initialize()
{
	// DXLib�̏�����
	if ( !SettingDxLib::InitDxLib() )
	{
		return false;
	}

	// �V�[�h�l
	srand((unsigned)time(nullptr));

	// �C���X�^���X����
	scene = new SceneManager;

	// FrameRate�̏�����
	FrameRate::Initialize();

	return true;
}

// ���C�����[�v
bool System::MainLoop()
{
	// �Q�[�����[�v
	while ( true )
	{
		/* ----- �X�V���� ----- */
		scene->Update();

		// FPS�̌v�Z
		FrameRate::CalcFPS();

		/* ----- �`�揈�� ----- */
		scene->Draw();

		// FPS�̕\��
		FrameRate::DrawFPS();

		// �Q�[���I��
		if ( scene->GetIsGameEnd() )
		{
			break;
		}

		// DxLib�̕`�揈��
		if ( !SettingDxLib::DrawDxLib() )
		{
			return false;
		}
	}

	return true;
}

// �I������
void System::Finalize()
{
	scene->Finalize();

	// Dx���C�u�����I������
	DxLib_End();
}

// ���C������
bool System::Main()
{
	// ����������
	if ( !Initialize() )
	{
		return false;
	}

	// ���C�����[�v�������s��
	if ( !MainLoop() )
	{
		return false;
	}

	// �I������
	Finalize();

	return true;
}