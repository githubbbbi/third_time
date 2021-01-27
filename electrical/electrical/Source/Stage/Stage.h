#pragma once

#include "../Define/Define.h"

// マップチップに対応する値
enum MapChip
{
	e_MAP_NONE = -1,			// なし
	e_MAP_BLOCK,				// ブロック
	e_MAP_GOAL_LEFT_BOTTOM,		// ゴール左下
	e_MAP_GOAL_RIGHT_BOTTOM,	// ゴール右下
	e_MAP_GOAL_LEFT_TOP,		// ゴール左上
	e_MAP_GOAL_RIGHT_TOP,		// ゴール左上
	e_MAP_NUM,					// マップチップ数
	e_MAP_GOAL					// ゴール
};

class Stage
{
private:
	int graphIndex;

	static int mapData[MAP_COUNT_Y][MAP_COUNT_X];

	// マップ描画
	void MapDraw(int x, int y, float shakeX, float shakeY, int scrollX, int scrollY);

public:
	Stage();

	// 初期化処理
	bool Initialize();

	// 描画処理
	void Draw(float shakeX, float shakeY,
			  int scrollX, int scrollY, int screenX, int screenY);

	//マップチップの値を取得
	static int GetMapParam(float x, float y);
};