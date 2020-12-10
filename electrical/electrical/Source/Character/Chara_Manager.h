#pragma once

#include <vector>

#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyAbsorption.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<CharaEnemyBase *>enemys;

	int playerGH;
	int enemyAbsorptionGH;

	// エネミー管理
	void EnemyManager();

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
	void Draw();
};