#pragma once

#include <vector>
#include "../Stage/Stage.h"
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBase.h"

class Graphic
{
private:
	std::vector<int> images;
	int player[4 * e_P_STATE_NUM];	// プレイヤー
	int enemyBomb;					// 爆弾エネミー
	int enemyElectric;				// 銃エネミー
	int enemyWater;					// 水弾エネミー
	int electricGun;				// 電気銃
	int waterGun;					// 水銃
	int particle;					// パーティクル
	int map[e_MAP_NUM];				// マップ

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

	int GetPlayer(int index);
	int GetEnemyBomb();
	int GetEnemyElectric();
	int GetEnemyWater();
	int GetElectricGun();
	int GetWaterGun();
	int GetParticle();
	int GetMap(int index);
};