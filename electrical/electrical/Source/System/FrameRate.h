#pragma once

class FrameRate
{
private:
	static long long baseTime;		// Šî€‚Æ‚È‚é
	static long long fpsBaseTime;	// Šî€‚Æ‚È‚é(fps—p)
	static float fps;				// FPS

	FrameRate();
public:
	// ‰Šú‰»ˆ—
	static void Initialize();

	// FPS‚ğŒvZ
	static void CalcFPS();

	// FPS‚ğ•\¦
	static void DrawFPS();
};