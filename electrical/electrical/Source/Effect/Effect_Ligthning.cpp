#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include "Effect_Ligthning.h"

Effect_Lightning::Effect_Lightning(int wallX, int wallY, int wallX2, int wallY2)
{
	// 反射壁
	this->wallX = wallX;
	this->wallY = wallY;
	this->wallX2 = wallX2;
	this->wallY2 = wallY2;

	// 線
	this->posX = rand() % (wallX2 - wallX) + wallX;
	this->posY = rand() % (wallY2 - wallY) + wallY;
	this->posX2 = this->posX;
	this->posY2 = this->posY;
	this->oldPosX = this->posX;
	this->oldPosX2 = this->posX;
	this->oldPosY = this->posY;
	this->oldPosY2 = this->posY;

	// 方向
	valX = rand() % 16 - 8;
	valY = rand() % 12 - 6;

	timer = 0;

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
		valX = GetRand(16) - 8;

		if ( valY > 0 )
		{
			valY = GetRand(6);
		}
		else
		{
			valY = GetRand(6) * -1;
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
	DrawLineAA(posX, posY, posX2, posY2, GetColor(200, 200, 0), TRUE);
	DrawLineAA(oldPosX, oldPosY, oldPosX2, oldPosY2, GetColor(255, 255, 0), TRUE);
}