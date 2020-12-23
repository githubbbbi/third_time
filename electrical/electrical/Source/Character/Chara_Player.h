#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/ElectricGun.h"

const int BATTERY_DCREASE_TIME = 60 * 1;			// バッテリー減少タイム
const int BATTERY_CHARGE_TIME = (60 * 1) / 2;		// バッテリーチャージタイム
const int PLAYER_MAX_BATTERY = 100;					// 最大バッテリー
const int PLAYER_CONSUMPTION_BULLET_NUM = 5;		// 電力を消費する弾数

class Chara_Player:public CharaBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int battery;				// バッテリー
	int batteryTimer;			// バッテリー減少タイマー
	int batteryChargeTimer;		// バッテリーチャージタイマー
	int shotBulletNum;			// 撃った弾数

	// 移動
	void Move();

	// バッテリー減少
	void BatteryDecrease();

	// バッテリーチャージ
	void BatteryCharge();

	// バッテリー管理
	void BatteryManager();

public:
	Chara_Player(float x, float y, int radius,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 攻撃処理管理
	void WeaponManager(int electricGunGH);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(float shakeX, float shakeY);

	// 攻撃
	bool IsAttack();

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