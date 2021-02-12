#include "DxLib.h"
#include <math.h>
#include "Effect_Explosion.h"
#include "../Resource/Graphic.h"
#include "../Utility/Utility.h"

Effect_Explosion::Effect_Explosion(float x, float y, int blendDecrease)
{
	this->x = x;
	this->y = y;
	this->blendDecrease = blendDecrease;

	int number = rand() % 10 + 1;
	randAngle = (double)(rand() % 360);

	if ( number < 10 )
	{
		speed = (float)(rand() % 3);
		exRate = ((double)(rand() % 5) + 3.0) / 10.0;
		h = 50.0f;
		s = 255.0f;
		v = 200.0f;
	}
	else
	{
		speed = (float)(rand() % 2);
		exRate = ((double)(rand() % 2) + 1.0) / 10.0;
		h = 0.0f;
		s = 0.0f;
		v = 200.0f;
	}

	frame = 0;
	blendValue = 255;
	isActive = true;

	r = 255.0f;
	g = 255.0f;
	b = 255.0f;
}

// ˆÚ“®
void Effect_Explosion::Move()
{
	if ( !isActive )
	{
		return;
	}

	x += speed * (float)cos(randAngle * DX_PI / 180);
	y -= speed * (float)sin(randAngle * DX_PI / 180);

	frame++;
	blendValue -= blendDecrease;
	exRate += 0.01;
}

// Á‹Ž
void Effect_Explosion::Erase()
{
	if ( blendValue <= 0 )
	{
		isActive = false;
	}
}

// XVˆ—
void Effect_Explosion::Update()
{
	Move();
	Erase();

	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// •`‰æˆ—
void Effect_Explosion::Draw(int scrollX, int scrollY,
							int displaceX, int  displaceY)
{
	if ( !isActive )
	{
		return;
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, blendValue);
	SetDrawBright((int)r, (int)g, (int)b);

	DrawRotaGraph((int)x - scrollX + displaceX,
				  (int)y - scrollY + displaceY,
				  exRate, 0.0, Graphic::GetInstance()->GetParticle(), true);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// isActive‚ðŽæ“¾
bool Effect_Explosion::GetIsActive()
{
	return isActive;
}