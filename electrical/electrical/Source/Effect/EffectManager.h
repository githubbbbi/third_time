#pragma once

#include <vector>
#include "Effect_Explosion.h"
#include "Effect_Clear.h"

// このクラスではメインゲームで使用するエフェクトのみを管理する
class EffectManager
{
private:
	std::vector<Effect_Explosion *>explosion;
	std::vector<Effect_Clear * > clear;

	float shakeX, shakeY;
	float shakeAddX, shakeAddY;

public:
	EffectManager();
	~EffectManager();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);

	// shakeXを取得
	float GetShakeX();

	// shakeYを取得
	float GetShakeY();

	// シェイク
	void Shake();

	// 爆発
	void Explosion(float x, float y);

	// クリア
	void Clear(float x, float y);
};