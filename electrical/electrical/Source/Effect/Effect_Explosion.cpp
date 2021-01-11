#include "Effect_Explosion.h"

Effect_Explosion::Effect_Explosion(float x, float y, int particleGH)
{
	this->x = x;
	this->y = y;
	this->particleGH = particleGH;
	isActive = true;
}

// XVˆ—
void Effect_Explosion::Update()
{

}
#include "DxLib.h"
// •`‰æˆ—
void Effect_Explosion::Draw(int scrollX, int scrollY)
{
	DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
				  1.0, 0.0, particleGH, true);
}

// isActive‚ğæ“¾
bool Effect_Explosion::GetIsActive()
{
	return isActive;
}