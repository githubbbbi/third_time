#pragma once

class FrameRate
{
private:
	static long long baseTime;		// ��ƂȂ鎞��
	static long long fpsBaseTime;	// ��ƂȂ鎞��(fps�p)
	static float fps;				// FPS

	FrameRate();
public:
	// ����������
	static void Initialize();

	// FPS���v�Z
	static void CalcFPS();

	// FPS��\��
	static void DrawFPS();
};