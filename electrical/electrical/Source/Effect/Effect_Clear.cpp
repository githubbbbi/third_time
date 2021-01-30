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
	h =  60.0f;
	s = 230.0f;
	v = 255.0f;

	isActive = true;

	playerX = x;
	playerY = y;
}

// 移動
void Effect_Clear::Move()
{
	if (isActive)
	{
		y -= speed;

		// 透明度を下げる
		transparency -= 10;
	}
}

// 消去
void Effect_Clear::Erase()
{
	// 透明度が0以下の時
	if (transparency <= 0)
	{
		isActive = false;
	}
}

// 更新処理
void Effect_Clear::Update()
{
	// 移動
	Move();

	// 消去
	Erase();

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Effect_Clear::Draw(int scrollX, int scrollY)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, transparency);

	SetDrawBright((int)r, (int)g, (int)b);

	DrawRotaGraph((int)(playerX + x) - scrollX, (int)(playerY + y) - scrollY,
				  exRate, angle, Graphic::GetInstance()->GetParticle(), true);

	SetDrawBright(0xFF, 0xFF, 0xFF);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// isActiveを取得
bool Effect_Clear::GetIsActive()
{
	return isActive;
}