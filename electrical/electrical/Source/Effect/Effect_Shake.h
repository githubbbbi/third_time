#pragma once

const float SHAKE_DECREASE = 0.3f;

class Effect_Shake
{
private:
	Effect_Shake();

public:
	// シェイク
	static void Shake(float *shakeX, float *shakeY,
					  float *addX, float *addY);
};