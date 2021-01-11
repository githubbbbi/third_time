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

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw(int scrollX, int scrollY);

	// isActive‚ğæ“¾
	bool GetIsActive();
};