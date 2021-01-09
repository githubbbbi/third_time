#include "DxLib.h"
#include "EffectManager.h"
#include "Effect_Shake.h"

EffectManager::EffectManager(int particleGH)
{
	shakeX = shakeY = 0.0f;
	shakeAddX = shakeAddY = 0.0f;

	this->particleGH = particleGH;
}

EffectManager::~EffectManager()
{

}

// 更新処理
void EffectManager::Update()
{
	// シェイク
	Effect_Shake::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddY);
}

// 描画処理
void EffectManager::Draw()
{

}

// shakeXを取得
float EffectManager::GetShakeX()
{
	return shakeX;
}

// shakeYを取得
float EffectManager::GetShakeY()
{
	return shakeY;
}

// シェイク
void EffectManager::Shake()
{
	shakeAddX = shakeAddY = 4.0f;
}

// 爆発
void EffectManager::Explosion(float x, float y)
{
	explosion.push_back(new Effect_Explosion(x, y));
}