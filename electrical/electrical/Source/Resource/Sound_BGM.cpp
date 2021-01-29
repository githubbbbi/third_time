#include "DxLib.h"
#include "Sound_BGM.h"

Sound_BGM::Sound_BGM()
{
	// 読み込み
	title = MyLoadSoundMem("Resource/Sound/BGM/title.mp3");
	game = MyLoadSoundMem("Resource/Sound/BGM/game.mp3");

	// サウンドの音量を設定
	MyChangeVolumeSoundMem();
}

// サウンドの音量を設定
void Sound_BGM::MyChangeVolumeSoundMem()
{
	for ( unsigned i = 0; i < BGM.size(); i++ )
	{
		ChangeVolumeSoundMem((int)(255.0f * 70.0f / 100.0f), BGM[i]);
	}

	ChangeVolumeSoundMem((int)(255.0f * 40.0f / 100.0f), game);
}

// 今までロードしたBGMを解放する
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


// サウンドの再生をチェック、再生
void Sound_BGM::CheckAndPlay(int soundHandle)
{
	if ( CheckSoundMem(soundHandle) )
	{
		return;
	}

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

// サウンドの再生をチェック、停止
void Sound_BGM::CheckAndStop(int soundHandle)
{
	if ( !CheckSoundMem(soundHandle) )
	{
		return;
	}

	StopSoundMem(soundHandle);
}

// BGM再生
void Sound_BGM::PlayBGM(BGM_Info bgm)
{
	switch ( bgm )
	{
		case e_TITLE_BGM:
			// タイトル
			CheckAndPlay(title);
			break;

		case e_GAME_BGM:
			// ゲーム
			CheckAndPlay(game);
			break;

		default:
			break;
	}
}

// BGM停止
void Sound_BGM::StopBGM(BGM_Info bgm)
{
	switch ( bgm )
	{
		case e_TITLE_BGM:
			// タイトル
			CheckAndStop(title);
			break;

		case e_GAME_BGM:
			// ゲーム
			CheckAndStop(game);
			break;

		default:
			break;
	}
}