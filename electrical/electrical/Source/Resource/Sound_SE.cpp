#include "DxLib.h"
#include "Sound_SE.h"

Sound_SE::Sound_SE()
{

}

// ���܂Ń��[�h����SE���������
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