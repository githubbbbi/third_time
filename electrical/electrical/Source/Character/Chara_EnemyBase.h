#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	// シェイクスタート
	void ShakeStart(float *shakeAddX, float *shakeAddY);

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);

	// 初期化処理
	virtual void Initialize() = 0;

	// 更新処理
	virtual void Update(float *shakeAddX, float *shakeAddY) = 0;

	// 描画処理
	virtual void Draw(float shakeX, float shakeY) = 0;

	//敵の当たり判定
	virtual void EnemiesCollision();

};