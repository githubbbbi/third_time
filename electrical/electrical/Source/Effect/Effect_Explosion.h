#pragma once

class Effect_Explosion
{
private:
	float x;
	float y;

public:
	Effect_Explosion(float x, float y);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};