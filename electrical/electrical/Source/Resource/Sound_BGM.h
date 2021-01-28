#pragma once

#include <vector>

enum BGM_Info
{
	e_TITLE_BGM,	// タイトル
	e_GAME_BGM		// ゲーム
};

class Sound_BGM
{
private:
	std::vector<int> BGM;

	int title;		// タイトル
	int game;		// メインゲーム

	int MyLoadSoundMem(const char *filename);

	// サウンドの音量を設定
	void MyChangeVolumeSoundMem();

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

	/**
	 * @brief
	 * BGMを再生する
	 * @param BGM_Info bgm 再生するBGM
	 */
	void PlayBGM(BGM_Info bgm);

	/**
	 * @brief
	 * BGMを停止する
	 * @param BGM_Info bgm 停止するBGM
	 */
	void StopBGM(BGM_Info bgm);
};