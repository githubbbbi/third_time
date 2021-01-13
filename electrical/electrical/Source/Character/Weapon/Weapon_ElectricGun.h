#pragma once

#include "WeaponBase.h"

extern const float EG_SPEED;
extern const int EG_ALIVE_TIME;

class Weapon_ElectricGun:public WeaponBase
{
private:
	double exRate;	// 拡大率
	int aliveTimer;	// 生存タイマー

	// 移動
	void Move();

	// 消去
	void Erase();

public:
	Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
					   int eraseFrame, bool isCharaLeftWard, int graphHandle);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);
};