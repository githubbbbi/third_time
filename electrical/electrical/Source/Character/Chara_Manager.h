#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBomb *>enemyBomb;
	std::vector<Chara_EnemyElectric *>enemyElectric;
	std::vector<Chara_EnemyWater *>enemyWater;

	float explosionX;		// 爆発の中心となる座標
	float explosionY;		// 爆発の中心となる座標

	// エネミー管理
	void EnemyManager();

	// キャラクタ同士の当たり判定
	void CharaCollision();

	// 攻撃処理管理
	void WeaponManager();

	// 攻撃の当たり判定
	void AttackCollision();

public:
	Chara_Manager();
	~Chara_Manager();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// スクロールの中心座標を取得
	float GetScrollCenterX();
	float GetScrollCenterY();

	// 爆発の中心となるX座標を取得
	float GetExplosionPosX();

	// 爆発の中心となるY座標を取得
	float GetExplosionPosY();

	// エネミーの死亡を取得
	bool GetIsEnemyDeath();
};