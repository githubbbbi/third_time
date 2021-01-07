#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	// 画像の向きを変化
	void ChangeGraphicDirection();

	// シェイクスタート
	void ShakeStart(float *shakeAddX, float *shakeAddY);

	// ブロックが間にあるか探す
	bool IsBlock(float playerX);

public:
	Chara_EnemyBase(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);

	// 敵の当たり判定
	void EnemiesCollision();
};