#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBase.h"
#include "../Define/Define.h"

enum EnemysInfo
{
	e_EnemyBomb,		// ボム兵
	e_EnemyElectric,	// 電気銃エネミー
	e_EnemyWater,		// 水銃エネミー
	e_EnemyNum
};

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int spawnData[MAP_COUNT_Y][MAP_COUNT_X];		// スポーンデータ
	bool isEnemySpawn[MAP_COUNT_Y][MAP_COUNT_X];	// エネミースポーンフラグ

	float explosionX;								// 爆発の中心となる座標
	float explosionY;								// 爆発の中心となる座標

	// ファイル読み込み
	bool LoadFile();

	// エネミーの生成
	void EnemyGenerate(int screenX, int screenY);

	// エネミー管理
	void EnemyManager(int screenX, int screenY);

	// キャラクタ同士の当たり判定
	void CharaCollision();

	// 攻撃の当たり判定
	void AttackCollision();

public:
	Chara_Manager();
	~Chara_Manager();

	// 初期化処理
	bool Initialize();

	// 更新処理
	void Update(int screenX, int screenY);

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// スクロールの中心座標を取得
	float GetScrollCenterX();
	float GetScrollCenterY();

	// 爆発の中心となるX座標を取得
	float GetExplosionPosX();

	// 爆発の中心となるY座標を取得
	float GetExplosionPosY();

	// キャラクターの死亡を取得
	bool GetIsCharaDeath();

	// HPを取得
	int GetPlayerHp();

	// 最大HPを取得
	int GetPlayerMaxHp();

	// 最大バッテリーを取得
	int GetPlayerBattery();

	// バッテリーを取得
	int GetPlayerMaxBattery();
};