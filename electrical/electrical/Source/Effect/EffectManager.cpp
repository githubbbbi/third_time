#include "DxLib.h"
#include "EffectManager.h"
#include "Effect_Shake.h"

EffectManager::EffectManager()
{
	shakeX = shakeY = 0.0f;
	shakeAddX = shakeAddY = 0.0f;
}

EffectManager::~EffectManager()
{
	// ����
	// ����
	for ( int i = explosion.size() - 1; i >= 0; i-- )
	{
		if ( !explosion[i]->GetIsActive() )
		{
			delete explosion[i];
			explosion.erase(explosion.begin() + i);
		}
	}
}

// �X�V����
void EffectManager::Update()
{
	// �V�F�C�N
	Effect_Shake::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddY);

	//�@����
	for ( unsigned int i = 0; i < explosion.size(); i++ )
	{
		if ( explosion[i]->GetIsActive() )
		{
			explosion[i]->Update();
		}
	}

	// ����
	for ( int i = explosion.size() - 1; i >= 0; i-- )
	{
		if ( !explosion[i]->GetIsActive() )
		{
			delete explosion[i];
			explosion.erase(explosion.begin() + i);
		}
	}
}

// �`�揈��
void EffectManager::Draw(int scrollX, int scrollY)
{
	//�@����
	for ( unsigned int i = 0; i < explosion.size(); i++ )
	{
		if ( explosion[i]->GetIsActive() )
		{
			explosion[i]->Draw(scrollX, scrollY);
		}
	}
}

// shakeX���擾
float EffectManager::GetShakeX()
{
	return shakeX;
}

// shakeY���擾
float EffectManager::GetShakeY()
{
	return shakeY;
}

// �V�F�C�N
void EffectManager::Shake()
{
	shakeAddX = shakeAddY = 4.0f;
}

// ����
void EffectManager::Explosion(float x, float y)
{
	for ( int i = 0; i < 100; i++ )
	{
		explosion.push_back(new Effect_Explosion(x, y, 9));
	}
}