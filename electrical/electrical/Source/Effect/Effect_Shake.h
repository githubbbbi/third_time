#pragma once

extern const float SHAKE_DECREASE;

class Effect_Shake
{
private:
	Effect_Shake();

public:
	// シェイク
	static void Shake(float *shakeX, float *shakeY,
					  float *addX, float *addY);
};