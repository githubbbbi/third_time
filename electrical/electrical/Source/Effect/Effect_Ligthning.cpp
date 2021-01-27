#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include "Effect_Ligthning.h"
#include "../Utility/Utility.h"

Effect_Lightning::Effect_Lightning(int wallX, int wallY, int wallX2, int wallY2)
{
	// 反射壁
	this->wallX = wallX;
	this->wallY = wallY;
	this->wallX2 = wallX2;
	this->wallY2 = wallY2;

	// 線
	this->posX = (rand() % (wallX2 - wallX)) + wallX;
	this->posY = (rand() % (wallY2 - wallY)) + wallY;
	this->posX2 = this->posX;
	this->posY2 = this->posY;
	this->oldPosX = this->posX;
	this->oldPosX2 = this->posX;
	this->oldPosY = this->posY;
	this->oldPosY2 = this->posY;

	// 方向
	valX = (rand() % 16) - 8;
	valY = (rand() % 12) - 6;

	timer = 0;

	color[0] = { 255.0f, 255.0f, 255.0f,
				 240.0f, 50.0f, 255.0f };
	color[1] = { 255.0f, 255.0f, 255.0f,
				 240.0f, 50.0f, 255.0f };
}

// 飛距離
bool Effect_Lightning::IsLengthOver()
{
	if ( timer == 10 )
	{
		return true;
	}

	return false;
}

// 更新処理
void Effect_Lightning::Update()
{
	Move();
	LightningCollision();
	// HSVからRGBへ変換
	for ( int i = 0; i < 2; i++ )
	{
		Utility::ConvertHSVtoRGB(&color[i].r, &color[i].g, &color[i].b,
								 color[i].h, color[i].s, color[i].v);
	}
}

void Effect_Lightning::Move()
{
	posX2 += valX;
	posY2 += valY;
	timer++;
	if ( timer % 5 == 0 )
	{
		// 追い線に保存
		oldPosX = posX;
		oldPosX2 = posX2;
		oldPosY = posY;
		oldPosY2 = posY2;

		// 開始地点更新
		posX = posX2;
		posY = posY2;

		//角度を大きく変更しない
		valX = (rand() % 16) - 8;

		if ( valY > 0 )
		{
			valY = rand() % 6;
		}
		else
		{
			valY = (rand() % 6) * -1;
		}
	}
}

void Effect_Lightning::LightningCollision()
{
	if ( posX2 < wallX || posX2 > wallX2 || posY2 < wallY || posY2 > wallY2 )
	{
		valX *= -1;
		valY *= -1;
	}
}


// 描画処理
void Effect_Lightning::Draw()
{
	DrawLineAA((float)posX, (float)posY,
			   (float)posX2, (float)posY2,
			   GetColor((int)color[0].r, (int)color[0].g, (int)color[0].b), 1.0f);

	DrawLineAA((float)oldPosX, (float)oldPosY,
			   (float)oldPosX2, (float)oldPosY2,
			   GetColor((int)color[1].r, (int)color[1].g, (int)color[1].b), 1.0f);
}