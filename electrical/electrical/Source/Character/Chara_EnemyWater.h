#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

enum EnemyWaterState
{
	e_EW_STATE_IDLE,				// 待機
	e_EW_STATE_ATTACK,				// 攻撃
	e_EW_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_EW_STATE_NUM
};

extern const int EW_WIDTH;						// 横幅
extern const int EW_HEIGHT;						// 縦幅
extern const int EW_BULLET_INTERVAL;			// 間隔
extern const int EW_MOTION[e_EW_STATE_NUM][4];	// モーション

class Chara_EnemyWater:public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// 銃を撃つ間隔
	float bulletSpeed;		// 銃のスピード

	// 移動
	void Move();

	// 武器処理管理
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive);

	// 攻撃管理
	void AttackManager(float playerX, float playerY, bool isPlayerAlive);

	// 向きを変更
	void ChangeDirection(float playerX);

	// 状態
	void State();

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower, int mapChipX, int mapChipY);
	~Chara_EnemyWater();

	// 更新処理
	void Update(float playerX, float playerY, bool isPlayerAlive) override;

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	void HitAttack() override;
};