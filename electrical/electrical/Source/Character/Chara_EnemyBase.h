#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	bool blockFlag;		//ブロックがあるかないかのフラグ
	float enemySpace;	//プレイヤーと敵のブロック個数

	// シェイクスタート
	void ShakeStart(float *shakeAddX, float *shakeAddY);

public:
	Chara_EnemyBase(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);

	//敵の当たり判定
	void EnemiesCollision();

	// ブロックが間にあるか探す
	void FindBlock(float playerX);
};