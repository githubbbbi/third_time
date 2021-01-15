#pragma once

#include <vector>
#include "../Stage/Stage.h"

class Graphic
{
private:
	static std::vector<int> images;
	static int player;			// プレイヤー
	static int enemyBomb;		// 爆弾エネミー
	static int enemyElectric;	// 銃エネミー
	static int enemyWater;		// 水弾エネミー
	static int electricGun;		// 電気銃
	static int waterGun;		// 水銃
	static int particle;		// パーティクル
	static int map[e_MAP_KIND_NUM];

	static int myLoadGraph(const char *filename);
	static int myLoadDivGraph(const char *fileName, int n,
							  int xn, int yn, int w, int h, int *buf);

public:
	Graphic() = default;
	~Graphic() = default;

	static void Load();

	// 今までロードした画像を解放する
	static void Release();

	static int GetPlayer();
	static int GetEnemyBomb();
	static int GetEnemyElectric();
	static int GetEnemyWater();
	static int GetElectricGun();
	static int GetWaterGun();
	static int GetParticle();
	static int GetMap(int index);
};