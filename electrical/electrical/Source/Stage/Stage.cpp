#include "DxLib.h"
#include "Stage.h"
#include "../Resource/Graphic.h"
#include "../Resource/CSV.h"

int Stage::mapData[MAP_COUNT_Y][MAP_COUNT_X] = { 0 };

Stage::Stage()
{
	graphIndex = 0;
}

// 初期化処理
bool Stage::Initialize()
{
	// 読み込むファイル名を格納する
	char fileName[512];
	sprintf_s(fileName, sizeof(fileName),
			  "Resource/Data/Stage/stage%d.csv", 1);

	// ファイルが読み込めない場合、false
	int *p = (int *)mapData;
	if ( !CSV::LoadFile(fileName, MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// マップ描画
void Stage::MapDraw(int x, int y, float shakeX, float shakeY,
					int scrollX, int scrollY, int displaceX, int displaceY)
{
	switch ( mapData[y][x] )
	{
		case e_MAP_NONE:
			// なし
			graphIndex = e_MAP_NONE;
			break;

		case e_MAP_BLOCK:
			// ブロック
			graphIndex = e_MAP_BLOCK;
			break;
		case e_MAP_GOAL_LEFT_BOTTOM:
			// ゴール左下
			graphIndex = e_MAP_GOAL_LEFT_BOTTOM;
			break;

		case e_MAP_GOAL_RIGHT_BOTTOM:
			// ゴール右下
			graphIndex = e_MAP_GOAL_RIGHT_BOTTOM;
			break;

		case e_MAP_GOAL_LEFT_TOP:
			// ゴール左上
			graphIndex = e_MAP_GOAL_LEFT_TOP;
			break;

		case e_MAP_GOAL_RIGHT_TOP:
			// ゴール右上
			graphIndex = e_MAP_GOAL_RIGHT_TOP;
			break;

		default:
			graphIndex = e_MAP_NONE;
			break;
	}

	if ( graphIndex != e_MAP_NONE )
	{
		DrawGraph(x * CHIP_SIZE + (int)shakeX - scrollX + displaceX,
				  y * CHIP_SIZE + (int)shakeX - scrollY + displaceY,
				  Graphic::GetInstance()->GetMapChip(graphIndex), true);
	}
}

// 描画処理
void Stage::Draw(float shakeX, float shakeY, int scrollX, int scrollY,
				 int screenX, int screenY, int displaceX, int displaceY)
{
	// スクリーンに映っている部分(2ブロック分多く)だけを描画
	int mapChipLeft = (screenX - displaceX +
					   (displaceX / (screenX / (WIN_WIDTH / 2))) - WIN_WIDTH / 2) / CHIP_SIZE - 2;
	int mapChipRight = (screenX - displaceX -
						(displaceX / (screenX / (WIN_WIDTH / 2))) + WIN_WIDTH / 2) / CHIP_SIZE + 2;
	int mapChipTop = (screenY - displaceY +
					  (displaceY / (screenY / (WIN_HEIGHT / 2))) - WIN_HEIGHT / 2) / CHIP_SIZE - 2;
	int mapChipBottom = (screenY - displaceY -
						 (displaceY / (screenY / (WIN_HEIGHT / 2))) + WIN_HEIGHT / 2) / CHIP_SIZE + 2;

	printfDx("%d, %d, %d, %d\n", mapChipLeft, mapChipRight, displaceX, screenX);

	if ( mapChipLeft < 0 )
	{
		mapChipLeft = 0;
	}

	if ( mapChipRight > MAP_COUNT_X )
	{
		mapChipRight = MAP_COUNT_X;
	}

	if ( mapChipTop < 0 )
	{
		mapChipTop = 0;
	}

	if ( mapChipBottom > MAP_COUNT_Y )
	{
		mapChipBottom = MAP_COUNT_Y;
	}

	for ( int y = mapChipTop; y < mapChipBottom; y++ )
	{
		for ( int x = mapChipLeft; x < mapChipRight; x++ )
		{
			MapDraw(x, y, shakeX, shakeY,
					scrollX, scrollY, displaceX, displaceY);
		}
	}


}

// マップチップの値を取得
int Stage::GetMapParam(float x, float y)
{
	// マップチップ配列の添え字
	int mapX = (int)x / CHIP_SIZE;
	int mapY = (int)y / CHIP_SIZE;

	// マップから出ていた場合、NONEを返す
	if ( mapX < 0 || mapY < 0 ||
		mapX >= MAP_COUNT_X ||
		mapY >= MAP_COUNT_Y )
	{
		return e_MAP_NONE;
	}

	// ゴールのマップチップはまとめてゴールと返す
	if ( mapData[mapY][mapX] == e_MAP_GOAL_LEFT_BOTTOM ||
		mapData[mapY][mapX] == e_MAP_GOAL_RIGHT_BOTTOM ||
		mapData[mapY][mapX] == e_MAP_GOAL_LEFT_TOP ||
		mapData[mapY][mapX] == e_MAP_GOAL_RIGHT_TOP )
	{
		return e_MAP_GOAL;
	}

	// マップチップ配列の値を返す
	return mapData[mapY][mapX];
}