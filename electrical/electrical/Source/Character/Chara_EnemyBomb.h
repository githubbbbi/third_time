#pragma once

#include "Chara_EnemyBase.h"

const int E_BOMB_WIDTH = 30;			// 横幅
const int E_BOMB_HEIGHT = 30;			// 縦幅
const float E_BOMB_NORMAL_SPEED = 2.0f;	// 通常スピード
const float E_BOMB_DASH_SPEED = 8.0f;	// ダッシュスピード

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// 移動
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// 攻撃ヒット
	void HitAttack(float *shakeAddX, float *shakeAddY);
};