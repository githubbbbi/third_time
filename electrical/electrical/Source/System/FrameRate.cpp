#include "FrameRate.h"
#include "DxLib.h"
#include "../Input/InputKey.h"

// �ϐ�������
long long FrameRate::baseTime = 0;
long long FrameRate::fpsBaseTime = 0;
float FrameRate::fps = 0.0f;

// ����������
void FrameRate::Initialize()
{
	baseTime = GetNowHiPerformanceCount();
	fpsBaseTime = GetNowHiPerformanceCount();
	fps = 0.0f;
}

// FPS���v�Z
void FrameRate::CalcFPS()
{
	// �t���[����
	static int count = 0;
	count++;

	// ���ݎ������擾(�}�C�N���b)
	long long currentTime = GetNowHiPerformanceCount();

	// ����������ݎ����ɐݒ�
	baseTime = currentTime;

	// 1�b�o��
	const int time = 1000000;
	if ( currentTime - fpsBaseTime >= time )
	{
		fps = (float)(count * time) / (float)(currentTime - fpsBaseTime);
		fpsBaseTime = currentTime;	// ����������ݎ����ɐݒ�
		count = 0;					// ���Z�b�g
	}
}

// FPS��\��
void FrameRate::DrawFPS()
{
	// �f�o�b�O�\��
	static bool isDrawFPS = false;
	if ( InputKey::IsKeyInputTrigger(KEY_INPUT_F1) )
	{
		isDrawFPS = !isDrawFPS;
	}

	if ( isDrawFPS )
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.ffps\n", fps);
	}
}