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

	// Load()���Ă΂��ƃR���X�g���N�^���Ă΂��
	void Load() {};

	// ���܂Ń��[�h����SE���������
	void Release();
};