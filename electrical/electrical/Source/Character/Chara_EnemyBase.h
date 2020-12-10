#pragma once

#include "CharaBase.h"

class CharaEnemyBase:public CharaBase
{
protected:
	

public:
	CharaEnemyBase(float x, float y, int radius,
				   float speed, int hp, int attackPower, int graphHandle);

	// isAliveを取得
	bool GetIsAlive();

	// ダメージを受ける
	void ReceiveDamage(int playerAttackPower);

	// 初期化処理
	virtual void Initialize() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw() = 0;
};