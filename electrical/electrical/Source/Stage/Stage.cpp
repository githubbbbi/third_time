#include "DxLib.h"
#include "Stage.h"

int Stage::mapData[][MAP_COUNT_X] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{ 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1,-1},
			{ 0,-1,-1,-1,-1,-1,-1, 0,-1,-1, 0, 0, 0,-1,-1},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Stage::Stage(int mapGH[])
{
	for ( int i = 0; i < e_MAP_KIND_NUM; i++ )
	{
		this->mapGH[i] = mapGH[i];
	}

	graphIndex = 0;
}

// 更新処理
void Stage::Update()
{

}

// マップ描画
void Stage::MapDraw(int x, int y, float shakeX, float shakeY)
{
	switch ( mapData[y][x] )
	{
		case e_MAP_NONE:
			// なし
			graphIndex = e_MAP_NONE;
			break;

		case e_MAP_BLOCK:
			// ブロック
			graphIndex = 0;
			break;

		default:
			graphIndex = e_MAP_NONE;
			break;
	}

	if ( graphIndex != e_MAP_NONE )
	{
		DrawGraph(x * CHIP_SIZE + (int)shakeX,
			y * CHIP_SIZE + (int)shakeX,
			mapGH[graphIndex], true);
	}
}

// 描画処理
void Stage::Draw(float shakeX, float shakeY)
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			MapDraw(x, y, shakeX, shakeY);
		}
	}
}

// マップチップの値を取得
int Stage::GetMapParam(float x, float y)
{
	// マップチップ配列の添え字
	int mapX, mapY;

	mapX = (int)x / CHIP_SIZE;
	mapY = (int)y / CHIP_SIZE;

	// マップから出ていた場合、-1を返す
	if ( mapX < 0 || mapY < 0 ||
		mapX >= MAP_COUNT_X ||
		mapY >= MAP_COUNT_Y )
	{
		return -1;
	}

	// マップチップ配列の値を返す
	return mapData[mapY][mapX];
}