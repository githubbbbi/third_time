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

// �X�V����
void EffectManager::Update()
{
	// �V�F�C�N
	Effect_Shake::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddY);
}

// �`�揈��
void EffectManager::Draw()
{

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
	explosion.push_back(new Effect_Explosion(x, y));
}