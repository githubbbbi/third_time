#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

const int E_GUN_WIDTH = 30;				// 横幅
const int E_GUN_HEIGHT = 30;			// 縦幅
const float E_GUN_NORMAL_SPEED = 3.0f;	// 通常スピード
const float E_GUN_DASH_SPEED = 5.0f;	// ダッシュスピード

const int BULLET_INTERVAL = 70;

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// 撃った弾数
	int bulletInterval;		// 銃を撃つ間隔
	bool isTargetLock;		// 範囲内のフラグ


	// 移動
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyGun(float x, float y, int radius, int width, int height,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// 武器処理管理
	void WeaponManager(int electricGunGH);

	// 攻撃ヒット
	void HitAttack(int index);

	// 電気銃の要素数
	unsigned int GetGunSize();

	// 電気銃のX座標取得
	float GetGunPosX(int index);

	// 電気銃のY座標取得
	float GetGunPosY(int index);

	// 電気銃のradius取得
	int GetGunRadius(int index);
};