#pragma once

#include <vector>

enum SE_Info
{
	e_GAME_START_SE,			// ゲームスタート
	e_PLAYER_JUMP_SE,			// プレイヤーのジャンプ
	e_PLAYER_CHAGING_SE,		// 充電中
	e_SHOT_ELECTRIC_GUN_SE,		// 電気銃を撃つ
	e_SHOT_WATER_GUN_SE,		// 水銃を撃つ
	e_RECEIVE_DAMAGE_SE,		// ダメージを受ける
	e_DEATH_SE,					// 死亡
	e_OPEN_HELP_SE,				// ヘルプを開く
	e_SCROLL_SE,				// スクロール
	e_STAGE_CLEAR_SE			// ステージクリア
};

class Sound_SE
{
private:
	std::vector<int> SE;

	int gameStart;			// ゲームスタート
	int playerJump;			// プレイヤーのジャンプ
	int playerCharging;		// 充電中
	int shotElectricGun;	// 電気銃を撃つ
	int shotWaterGun;		// 水銃を撃つ
	int receiveDamage;		// ダメージを受ける
	int death;				// 死亡
	int openHelp;			// ヘルプを開く
	int scroll;				// スクロール
	int stageClear;			// ステージクリア

	int MyLoadSoundMem(const char *filename);

	// サウンドの音量を設定
	void MyChangeVolumeSoundMem();

public:
	Sound_SE();
	~Sound_SE() = default;

	static Sound_SE *GetInstance()
	{
		static Sound_SE SE;
		return &SE;
	}

	// Load()が呼ばれるとコンストラクタが呼ばれる
	void Load()
	{
	};

	// 今までロードしたSEを解放する
	void Release();

	/**
	 * @brief
	 * SEを再生する
	 * @param SE_Info se 再生するSE
	 * @param isCheckSound サウンドが再生されているかチェックする
	 */
	void PlaySE(SE_Info se, bool isCheckSound);

	/**
	 * @brief
	 * SEを停止する
	 * @param SE_Info se 停止するSE
	 */
	void StopSE(SE_Info se);

	// すべてのSEを停止する
	void StopAllSE();
};