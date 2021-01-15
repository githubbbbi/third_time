#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_ElectricGun.h"

extern const int E_GUN_WIDTH;			// 横幅
extern const int E_GUN_HEIGHT;			// 縦幅
extern const float E_GUN_NORMAL_SPEED;	// 通常スピード
extern const float E_GUN_DASH_SPEED;	// ダッシュスピード

const int BULLET_INTERVAL = 70;

class Chara_EnemyElectric:public Chara_EnemyBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int shotBulletNum;		// 撃った弾数
	int bulletInterval;		// 銃を撃つ間隔
	bool isTargetLock;		// 範囲内のフラグ

	// 自動移動
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// 移動
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyElectric(float x, float y, int radius, int width, int height,
						float speed, int hp, int attackPower);
	~Chara_EnemyElectric();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float playerX, float playerY, bool isPlayerAlive);

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// 武器処理管理
	void WeaponManager();

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

	// 電気銃のisLeftWard取得
	bool GetIsGunLeftWard(int index);
};