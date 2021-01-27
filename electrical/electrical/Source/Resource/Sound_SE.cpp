#include "DxLib.h"
#include "Sound_SE.h"

Sound_SE::Sound_SE()
{

}

// 今までロードしたSEを解放する
void Sound_SE::Release()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		DeleteGraph(SE[i]);
	}

	SE.clear();
}

int Sound_SE::MyLoadSoundMem(const char *filename)
{
	int temp = LoadSoundMem(filename);
	SE.push_back(temp);

	return temp;
}