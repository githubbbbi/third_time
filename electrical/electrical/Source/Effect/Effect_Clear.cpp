#include "DxLib.h"
#include "Effect_Clear.h"
#include "../Resource/Graphic.h"
#include "../Utility/Utility.h"

Effect_Clear::Effect_Clear(float x, float y)
{
	this->x = (float)(rand() % 57) - 28.0f;
	this->y = 30.0f;
	exRate = (double)(rand() % 4 + 2.0f) / 10.0;
	angle = (double)(rand() % 72);
	speed = (float)(rand() % 15 + 8.0f) / 10.0f;
	transparency = 255;

	r = 255.0f;
	g = 255.0f;
	b = 255.0f;
	h = 60.0f;
	s = 230.0f;
	v = 255.0f;

	isActive = true;

	playerX = x;
	playerY = y;
}

// �ړ�
void Effect_Clear::Move()
{
	if ( isActive )
	{
		y -= speed;

		// �����x��������
		transparency -= 10;
	}
}

// ����
void Effect_Clear::Erase()
{
	// �����x��0�ȉ��̎�
	if ( transparency <= 0 )
	{
		isActive = false;
	}
}

// �X�V����
void Effect_Clear::Update()
{
	// �ړ�
	Move();

	// ����
	Erase();

	// HSV����RGB�ɕϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void Effect_Clear::Draw(int scrollX, int scrollY,
						int displaceX, int  displaceY)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, transparency);

	SetDrawBright((int)r, (int)g, (int)b);

	DrawRotaGraph((int)(playerX + x) - scrollX + displaceX,
				  (int)(playerY + y) - scrollY + displaceY,
				  exRate, angle, Graphic::GetInstance()->GetParticle(), true);

	SetDrawBright(0xFF, 0xFF, 0xFF);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// isActive���擾
bool Effect_Clear::GetIsActive()
{
	return isActive;
}