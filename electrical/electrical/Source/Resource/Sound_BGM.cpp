#include "DxLib.h"
#include "Sound_BGM.h"

Sound_BGM::Sound_BGM()
{
}

void Sound_BGM::Release()
{
	for ( unsigned i = 0; i < BGM.size(); i++ )
	{
		DeleteGraph(BGM[i]);
	}

	BGM.clear();
}

int Sound_BGM::MyLoadSoundMem(const char *filename)
{
	int temp = LoadSoundMem(filename);
	BGM.push_back(temp);

	return temp;
}