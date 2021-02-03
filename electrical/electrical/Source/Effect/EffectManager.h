#pragma once

#include <vector>
#include "Effect_Explosion.h"
#include "Effect_Clear.h"

// ���̃N���X�ł̓��C���Q�[���Ŏg�p����G�t�F�N�g�݂̂��Ǘ�����
class EffectManager
{
private:
	std::vector<Effect_Explosion *>explosion;
	std::vector<Effect_Clear * > clear;

	float shakeX;		// �V�F�C�N��
	float shakeY;		// �V�F�C�N��
	float shakeAddX;	// �V�F�C�N���Z��
	float shakeAddY;	// �V�F�C�N���Z��

public:
	EffectManager();
	~EffectManager();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY,
			  int displaceX, int  displaceY);

	// shakeX���擾
	float GetShakeX();

	// shakeY���擾
	float GetShakeY();

	// �V�F�C�N
	void Shake();

	// ����
	void Explosion(float x, float y);

	// �N���A
	void Clear(float x, float y);
};