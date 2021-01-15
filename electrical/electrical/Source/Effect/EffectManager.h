#pragma once

#include <vector>
#include "Effect_Explosion.h"

class EffectManager
{
private:
	std::vector<Effect_Explosion *>explosion;

	float shakeX, shakeY;
	float shakeAddX, shakeAddY;

public:
	EffectManager();
	~EffectManager();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);

	// shakeX���擾
	float GetShakeX();

	// shakeY���擾
	float GetShakeY();

	// �V�F�C�N
	void Shake();

	// ����
	void Explosion(float x, float y);
};