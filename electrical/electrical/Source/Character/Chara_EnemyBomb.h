#pragma once

#include "Chara_EnemyBase.h"

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// 移動
	void Move(float playerX, float playerY);

public:
	Chara_EnemyBomb(float x, float y, int radius,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update(float playerX, float playerY,
				float *shakeAddX, float *shakeAddY) override;

	// 描画処理
	void Draw(float shakeX, float shakeY) override;

	// 攻撃処理管理
	void WeaponManager(int electricGunGH) override;
};