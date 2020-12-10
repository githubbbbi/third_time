#include "DxLib.h"
#include "ElectricGun.h"
#include "../../Define/Define.h"

ElectricGun::ElectricGun(float x, float y, int radius,
						 float speed, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->graphHandle = graphHandle;

	isAlive = true;
}

// XVˆ—
void ElectricGun::Update()
{
	x -= speed;

	if ( x + radius < 0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}
}

// •`‰æˆ—
void ElectricGun::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y,
					  1.0, 0.0, graphHandle, true);
	}
}

// ’e‚ªƒqƒbƒg‚µ‚½ê‡‚Ìˆ—
void ElectricGun::BulletHit()
{
	isAlive = false;
}

// XÀ•W‚ğæ“¾
float ElectricGun::GetPosX()
{
	return x;
}

// YÀ•W‚ğæ“¾
float ElectricGun::GetPosY()
{
	return y;
}

// ”¼Œa‚ğæ“¾
int ElectricGun::GetRadius()
{
	return radius;
}

bool ElectricGun::GetIsAlive()
{
	return isAlive;
}