#include "DxLib.h"
#include "System.h"
#include "SettingDxLib.h"

// �R���X�g���N�^
System::System()
{
	gameMain = new GameMain;
}

// �f�X�g���N�^
System::~System()
{
	delete gameMain;
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

// ����������
bool System::Initialize()
{
	// DXLib�̏�����
	if ( !DxLibInit() )
	{
		return false;
	}

	// ���C���Q�[��
	gameMain->Initialize();

	return true;
}

// ���C�����[�v
bool System::MainLoop()
{
	// �Q�[�����[�v
	while ( true )
	{
		/* ----- �X�V���� ----- */
		// ���C���Q�[��
		gameMain->Update();

		/* ----- �`�揈�� ----- */
		// ���C���Q�[��
		gameMain->Draw();

		// DxLib�̃��[�v����
		if ( !DxLibGameLoop() )
		{
			return false;
		}
	}

	return true;
}

// �I������
void System::Finalize()
{
	// Dx���C�u�����I������
	DxLib_End();
}