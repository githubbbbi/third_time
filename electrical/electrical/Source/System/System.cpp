#include "DxLib.h"
#include "System.h"
#include "SettingDxLib.h"
#include "../Mask/Mask.h"

// �R���X�g���N�^
System::System()
{
	gameMain = nullptr;
}

// �f�X�g���N�^
System::~System()
{
	delete gameMain;
}

// ����������
bool System::Initialize()
{
	// DXLib�̏�����
	if ( !SettingDxLib::DxLibInit() )
	{
		return false;
	}

	// �C���X�^���X����
	gameMain = new GameMain;

	// ���C���Q�[��
	gameMain->Initialize();

	// �}�X�N�Z�b�g
	Mask::SetMask();

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
		// �}�X�N�̕`��
		Mask::DrawMask();

		// ���C���Q�[��
		gameMain->Draw();

		// �}�X�N�̌㏈��
		Mask::LoopMask();

		// DxLib�̃��[�v����
		if ( !SettingDxLib::DxLibGameLoop() )
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