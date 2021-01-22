#pragma once

#include <vector>
#include "../Stage/Stage.h"
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBomb.h"
#include "../Character/Chara_EnemyElectric.h"
#include "../Character/Chara_EnemyWater.h"

class Graphic
{
private:
	std::vector<int> images;
	int mask;								// マスク画像
	int player[4 * e_P_STATE_NUM];			// プレイヤー
	int enemyBomb[4 * e_EB_STATE_NUM];		// 爆弾エネミー
	int enemyElectric[4 * e_EE_STATE_NUM];	// 銃エネミー
	int enemyWater[4 * e_EW_STATE_NUM];		// 水弾エネミー
	int electricGun;						// 電気銃
	int waterGun;							// 水銃
	int particle;							// パーティクル
	int map[e_MAP_NUM];						// マップ
	int background;							// 背景
	int uiPlayer;							// プレイヤーUI

	int MyLoadGraph(const char *filename);
	int MyLoadDivGraph(const char *fileName, int n,
					   int xn, int yn, int w, int h, int *buf);

public:
	Graphic();
	~Graphic() = default;

	static Graphic *GetInstance()
	{
		static Graphic graphic;
		return &graphic;
	}

	// Load()が呼ばれるとコンストラクタが呼ばれる
	void Load() {};

	// 今までロードした画像を解放する
	void Release();

	int GetMask();
	int GetPlayer(int index);
	int GetEnemyBomb(int index);
	int GetEnemyElectric(int index);
	int GetEnemyWater(int index);
	int GetElectricGun();
	int GetWaterGun();
	int GetParticle();
	int GetMap(int index);
	int GetBackground();
	int GetUIPlayer();
};