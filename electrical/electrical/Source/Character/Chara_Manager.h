#pragma once

#include <vector>
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBase.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int playerGH;			// プレイヤー
	int electricGunGH;		// 電気銃
	int enemyBombGH;		// 爆弾エネミー
	int enemyGunGH;		// 銃エネミー

	// エネミー管理
	void EnemyManager(float *shakeAddX, float *shakeAddY);

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
	void Update(float *shakeAddX, float *shakeAddY);

	// 描画処理
	void Draw(float shakeX, float shakeY);
};