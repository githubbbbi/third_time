#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyAbsorption:public CharaEnemyBase
{
private:
	// 移動
	void Move();

public:
	Chara_EnemyAbsorption(float x, float y, int radius,
						  float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyAbsorption();

	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw(float shakeX, float shakeY) override;
};