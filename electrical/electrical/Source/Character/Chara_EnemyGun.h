#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// 撃った弾数
	int bulletInterval;
	int targetlock;	//範囲内のフラグ
	
	// 移動
	void Move(float playerX, float playerY);

public:
	Chara_EnemyGun(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// 描画処理
	void Draw(float shakeX, float shakeY) override;

	// 攻撃処理管理
	void WeaponManager(int electricGunGH) override;

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