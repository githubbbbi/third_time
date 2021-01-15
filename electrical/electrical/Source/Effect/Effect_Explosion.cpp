#include "DxLib.h"
#include <math.h>
#include "Effect_Explosion.h"
#include "../Resource/Graphic.h"

Effect_Explosion::Effect_Explosion(float x, float y, int blendDecrease)
{
	this->x = x;
	this->y = y;
	this->blendDecrease = blendDecrease;

	number = rand() % 10 + 1;
	randAngle = (double)(rand() % 360);

	if ( number < 10 )
	{
		speed = (float)(rand() % 3);
		exRate = (double)(rand() % 5 + 3) / 10.0;
	}
	else
	{
		speed = (float)(rand() % 2);
		exRate = (double)(rand() % 2 + 1) / 10.0;
	}

	frame = 0;
	blendValue = 255;
	isActive = true;
}

// �ړ�
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

// ����
void Effect_Explosion::Erase()
{
	if ( blendValue <= 0 )
	{
		isActive = false;
	}
}

// �X�V����
void Effect_Explosion::Update()
{
	Move();
	Erase();
}

// �`�揈��
void Effect_Explosion::Draw(int scrollX, int scrollY)
{
	if ( !isActive )
	{
		return;
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, blendValue);
	if ( number < 10 )
	{
		SetDrawBright(255, 64, 0);
	}
	else
	{
		SetDrawBright(255, 255, 255);
	}

	DrawRotaGraph((int)x - scrollX, (int)y - scrollY,
				  exRate, 0.0, Graphic::GetParticle(), true);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// isActive���擾
bool Effect_Explosion::GetIsActive()
{
	return isActive;
}