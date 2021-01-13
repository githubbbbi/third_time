#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/Weapon_ElectricGun.h"

const int P_WIDTH = 50;							// 横幅
const int P_HEIGHT = 50;						// 縦幅
const float P_NORMAL_SPEED = 3.0f;				// 通常スピード
const float P_DASH_SPEED = 5.0f;				// ダッシュスピード
const int BATTERY_DCREASE_TIME = 60 * 1;		// バッテリー減少タイム
const int BATTERY_CHARGE_TIME = (60 * 1) / 2;	// バッテリーチャージタイム
const int P_MAX_BATTERY = 100;					// 最大バッテリー
const int P_CONSUMPTION_BULLET_NUM = 5;			// 電力を消費する弾数

class Chara_Player:public CharaBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int padInputX, padInputY;	// パッドレバーの入力量(キーボードの矢印キーの入力量も取得できる)
	int battery;				// バッテリー
	int batteryTimer;			// バッテリー減少タイマー
	int batteryChargeTimer;		// バッテリーチャージタイマー
	int shotBulletNum;			// 撃った弾数

	// 入力での移動
	void InputMove();

	// 移動
	void Move();

	// 画像の向きを変更
	void ChangeGraphicDirection();

	// バッテリー減少
	void BatteryDecrease();

	// バッテリーチャージ
	void BatteryCharge();

	// バッテリー管理
	void BatteryManager();

public:
	Chara_Player(float x, float y, int radius, int width, int height,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 武器処理管理
	void WeaponManager(int electricGunGH);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// 攻撃
	bool IsAttack();

	// 攻撃ヒット
	void HitAttack(int index);

	// 電気銃の要素数
	unsigned int GetGunSize();

	// 電気銃のX座標を取得
	float GetGunPosX(int index);

	// 電気銃のY座標を取得
	float GetGunPosY(int index);

	// 電気銃のradiusを取得
	int GetGunRadius(int index);

	// 電気銃のisLeftWardを取得
	bool GetIsGunLeftWard(int index);
};