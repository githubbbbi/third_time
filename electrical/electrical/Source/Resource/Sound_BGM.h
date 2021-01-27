#pragma once

#include <vector>

class Sound_BGM
{
private:
	std::vector<int> BGM;

	int MyLoadSoundMem(const char *filename);

public:
	Sound_BGM();
	~Sound_BGM() = default;

	static Sound_BGM *GetInstance()
	{
		static Sound_BGM BGM;
		return &BGM;
	}

	// Load()が呼ばれるとコンストラクタが呼ばれる
	void Load() {};

	// 今までロードしたSEを解放する
	void Release();
};