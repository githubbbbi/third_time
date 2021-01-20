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
	// ファイルが読み込めない場合、false
	int *p = (int *)mapData;
	if ( !CSV::LoadFile("Resource/Data/Stage/stage%d.csv",
						1, MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// 更新処理
void Stage::Update()
{

}

// マップ描画
void Stage::MapDraw(int x, int y, float shakeX, float shakeY, int scrollX, int scrollY)
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

		case e_MAP_THIN_FLOOR:
			// 薄い床
			graphIndex = 1;
			break;

		default:
			graphIndex = e_MAP_NONE;
			break;
	}

	if ( graphIndex != e_MAP_NONE )
	{
		DrawGraph(x * CHIP_SIZE + (int)shakeX - scrollX,
				  y * CHIP_SIZE + (int)shakeX - scrollY,
				  Graphic::GetInstance()->GetMap(graphIndex), true);

		DrawFormatString(x * CHIP_SIZE - scrollX, y * CHIP_SIZE - scrollY, GetColor(255, 255, 255), "%d,%d", x, y);
	}
}

// 描画処理
void Stage::Draw(float shakeX, float shakeY,
				 int scrollX, int scrollY, int screenX, int screenY)
{
	// スクリーンに映っている部分だけを描画
	int mapLeft = (screenX - WIN_WIDTH / 2) / CHIP_SIZE;
	int mapRight = (screenX + WIN_WIDTH / 2) / CHIP_SIZE + 1;
	int mapTop = (screenY - WIN_HEIGHT / 2) / CHIP_SIZE;
	int mapBottom = (screenY + WIN_HEIGHT / 2) / CHIP_SIZE + 1;

	for ( int y = mapTop; y < mapBottom; y++ )
	{
		for ( int x = mapLeft; x < mapRight; x++ )
		{
			MapDraw(x, y, shakeX, shakeY, scrollX, scrollY);
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

	// 薄い床
	if ( mapData[mapY][mapX] == e_MAP_THIN_FLOOR )
	{
		if ( y <= mapY * CHIP_SIZE - CHARA_SIZE / 2 )
		{
			return e_MAP_THIN_FLOOR;
		}

		return e_MAP_NONE;
	}

	// マップチップ配列の値を返す
	return mapData[mapY][mapX];
}