#include "DxLib.h"
#include "Sound_BGM.h"

Sound_BGM::Sound_BGM()
{
	// �ǂݍ���
	title = MyLoadSoundMem("Resource/Sound/BGM/title.mp3");
	game = MyLoadSoundMem("Resource/Sound/BGM/game.mp3");

	// �T�E���h�̉��ʂ�ݒ�
	MyChangeVolumeSoundMem();
}

// �T�E���h�̉��ʂ�ݒ�
void Sound_BGM::MyChangeVolumeSoundMem()
{
	for ( unsigned i = 0; i < BGM.size(); i++ )
	{
		ChangeVolumeSoundMem((int)(255.0f * 70.0f / 100.0f), BGM[i]);
	}

	ChangeVolumeSoundMem((int)(255.0f * 40.0f / 100.0f), game);
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

// BGM�Đ�
void Sound_BGM::PlayBGM(BGM_Info bgm)
{
	switch ( bgm )
	{
		case e_TITLE_BGM:
			// �^�C�g��
			if ( CheckSoundMem(title) )
			{
				break;
			}

			PlaySoundMem(title, DX_PLAYTYPE_BACK);
			break;

		case e_GAME_BGM:
			// �Q�[��
			if ( CheckSoundMem(game) )
			{
				break;
			}

			PlaySoundMem(game, DX_PLAYTYPE_BACK);
			break;

		default:
			break;
	}
}

// BGM��~
void Sound_BGM::StopBGM(BGM_Info bgm)
{
	switch ( bgm )
	{
		case e_TITLE_BGM:
			// �^�C�g��
			if ( !CheckSoundMem(title) )
			{
				break;
			}

			StopSoundMem(title);
			break;

		case e_GAME_BGM:
			// �Q�[��
			if ( !CheckSoundMem(game) )
			{
				break;
			}

			StopSoundMem(game);
			break;

		default:
			break;
	}
}