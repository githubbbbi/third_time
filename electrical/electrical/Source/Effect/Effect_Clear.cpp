#include "DxLib.h"
#include "Effect_Clear.h"
#include "../Resource/Graphic.h"

Effect_Clear::Effect_Clear(float x, float y)
{
	this->x = 0.0f;
	this->y = 0.0f;
	exRate = 1.0;
	angle = 0.0;

	playerX = x;
	playerY = y;
}

// �X�V����
void Effect_Clear::Update()
{

}

// �`�揈��
void Effect_Clear::Draw(int scrollX, int scrollY)
{
	DrawRotaGraph((int)(playerX + x) - scrollX, (int)(playerY + y) - scrollY,
				  exRate, angle, Graphic::GetInstance()->GetParticle(), true);
}

// isActive���擾
bool Effect_Clear::GetIsActive()
{
	return isActive;
}