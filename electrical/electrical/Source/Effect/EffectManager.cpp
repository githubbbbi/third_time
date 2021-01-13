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
	// 消去
	// 爆発
	for ( int i = explosion.size() - 1; i >= 0; i-- )
	{
		if ( !explosion[i]->GetIsActive() )
		{
			delete explosion[i];
			explosion.erase(explosion.begin() + i);
		}
	}
}

// 更新処理
void EffectManager::Update()
{
	// シェイク
	Effect_Shake::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddY);

	//　爆発
	for ( unsigned int i = 0; i < explosion.size(); i++ )
	{
		if ( explosion[i]->GetIsActive() )
		{
			explosion[i]->Update();
		}
	}

	// 消去
	for ( int i = explosion.size() - 1; i >= 0; i-- )
	{
		if ( !explosion[i]->GetIsActive() )
		{
			delete explosion[i];
			explosion.erase(explosion.begin() + i);
		}
	}
}

// 描画処理
void EffectManager::Draw(int scrollX, int scrollY)
{
	//　爆発
	for ( unsigned int i = 0; i < explosion.size(); i++ )
	{
		if ( explosion[i]->GetIsActive() )
		{
			explosion[i]->Draw(scrollX, scrollY);
		}
	}
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
	for ( int i = 0; i < 100; i++ )
	{
		explosion.push_back(new Effect_Explosion(x, y, 9, particleGH));
	}
}