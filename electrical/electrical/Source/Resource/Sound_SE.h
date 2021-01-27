#pragma once

#include <vector>

class Sound_SE
{
private:
	std::vector<int> SE;

	int MyLoadSoundMem(const char *filename);

public:
	Sound_SE();
	~Sound_SE() = default;

	static Sound_SE *GetInstance()
	{
		static Sound_SE SE;
		return &SE;
	}

	// Load()が呼ばれるとコンストラクタが呼ばれる
	void Load() {};

	// 今までロードしたSEを解放する
	void Release();
};