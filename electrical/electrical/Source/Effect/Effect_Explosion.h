#pragma once

class Effect_Explosion
{
private:
	float x;
	float y;
	bool isActive;

	int particleGH;

public:
	Effect_Explosion(float x, float y, int particleGH);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);

	// isActive���擾
	bool GetIsActive();
};