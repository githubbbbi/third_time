#include "DxLib.h"
#include "SettingDxLib.h"
#include "../Define/Define.h"
#pragma comment( lib, "winmm.lib" )

// �ϐ�������
long long SettingDxLib::baseTime = 0;
int SettingDxLib::refreshRate = 0;
unsigned long long SettingDxLib::frequency = 0;

// ����������
void SettingDxLib::Initialize()
{
	baseTime = GetNowHiPerformanceCount();
	frequency = GetSysPerformanceFrequency();
}

// �X���[�v
void SettingDxLib::MySleep(int flag)
{
	// flag��FALSE = Sleep�𖢎g�p(Vsync�g�p)
	if ( flag == FALSE )
	{
		return;
	}

	// 1�t���[���ɂ�������ŏ�����(�b)
	const float FRAME_TIME = 1.0f / (float)refreshRate;

	// ���ݎ������擾(�}�C�N���b)
	long long currentTime = GetNowHiPerformanceCount();

	// �o�ߎ���(�b) = (���̎��� - �O�t���[���̎���) / ���g��
	float frameTime = (float)(currentTime - baseTime) / (float)frequency;

	//�������Ԃɗ]�T������ꍇ�͂��̕��҂�
	if ( frameTime < FRAME_TIME )
	{
		//Sleep�̎���(�~���b)���v�Z
		DWORD sleepTime = (DWORD)((FRAME_TIME - frameTime) * 1000.0f);

		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);
	}

	baseTime = currentTime;	// ����������ݎ����ɐݒ�
}

// DxLib�̏���������
bool SettingDxLib::InitDxLib()
{
	int windowMode = TRUE;
	if ( MessageBox(NULL, "�t���X�N���[���ŋN�����܂����H",
					"�N���I�v�V����", MB_YESNO) == IDYES )
	{
		// �t���X�N���[�����[�h�ɐݒ�
		windowMode = FALSE;
	}
	else
	{
		// �E�B���h�E���[�h�ɐݒ�
		windowMode = TRUE;
	}

	// �E�B���h�E���[�h��ݒ�
	ChangeWindowMode(windowMode);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// �f�X�N�g�b�v�̉𑜓x���擾
	int desktopWidth, desktopHeight;
	GetDefaultState(&desktopWidth, &desktopHeight, NULL);

	// ���t���b�V�����[�g
	HDC hdc = GetDC(GetMainWindowHandle());			// �f�o�C�X�R���e�L�X�g�̎擾
	refreshRate = GetDeviceCaps(hdc, VREFRESH);		// ���t���b�V�����[�g�̎擾
	ReleaseDC(GetMainWindowHandle(), hdc);			// �f�o�C�X�R���e�L�X�g�̉��

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g���A�ő僊�t���b�V�����[�g��ݒ�(���j�^�[�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32, refreshRate);

	// 60�ȏ�̏ꍇ��60�ɐݒ�(60fps�ŌŒ�)
	if ( refreshRate >= 60 )
	{
		refreshRate = 60;
	}

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	double winExRate = 1.0;
	if ( windowMode == FALSE )
	{
		// �t���X�N���[�����͊g��
		winExRate = desktopWidth / WIN_WIDTH;
	}

	SetWindowSizeExtendRate(winExRate);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 0);

	// ��d�N���̐ݒ�
	SetDoubleStartValidFlag(FALSE);

	// ���������̐ݒ�
	SetWaitVSyncFlag(TRUE);

	// �o�b�N�O���E���h����
	SetAlwaysRunFlag(FALSE);

	// ���O�̏o�͐��ݒ�
	SetApplicationLogSaveDirectory("./");

	// DxLib�̏�����
	if ( DxLib_Init() == -1 )
	{
		// �ُ�I��
		return false;
	}

	// �}�E�X�\���ݒ�
	SetMouseDispFlag(TRUE);

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// ����������
	Initialize();

	// ����I��
	return true;
}

// DxLib�̕`�揈��
bool SettingDxLib::DrawDxLib()
{
	// (�_�u���o�b�t�@)����
	ScreenFlip();

	// �X���[�v
	MySleep(TRUE);

	// Windows�V�X�e�����炭�������������
	if ( ProcessMessage() == -1 )
	{
		return false;
	}

	// ��ʃN���A
	ClearDrawScreen();

	return true;
}