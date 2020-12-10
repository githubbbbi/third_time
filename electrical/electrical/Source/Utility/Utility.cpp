#include "Utility.h"
#include "../Define/Define.h"
#include <math.h>
#include "DxLib.h"

// 画面内にとどまる
void Utility::StayOnScreen(float *x, float *y, int radius,
						   bool isStayX, bool isStayY)
{
	if ( isStayX )
	{
		if ( *x - radius < 0 )
		{
			*x = (float)0 + (float)radius;
		}
		else if ( *x + radius > WIN_WIDTH )
		{
			*x = (float)WIN_WIDTH - (float)radius;
		}
	}

	if ( isStayY )
	{
		if ( *y - radius < 0 )
		{
			*y = (float)0 + (float)radius;
		}
		else if ( *y + radius > WIN_HEIGHT )
		{
			*y = (float)WIN_HEIGHT - (float)radius;
		}
	}
}



// マップチップの値を取得
int Utility::GetMapParam(float x, float y)
{
	// テスト用
	int mapData[MAP_COUNT_Y][MAP_COUNT_X] =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	// マップチップ配列の添え字
	int mapX, mapY;

	mapX = (int)x / CHIP_SIZE;
	mapY = (int)y / CHIP_SIZE;

	// マップから出ていた場合、-1を返す
	if ( mapX < 0 || mapY < 0 ||
		mapX >= MAP_COUNT_X || mapY >= MAP_COUNT_Y )
	{
		return -1;
	}

	// マップチップ配列の値を返す
	return mapData[mapY][mapX];
}

// マップとの当たり判定
// 1：左辺に衝突、2：右辺に衝突、3：上辺、4：下辺
int Utility::MapHitCheck(float x, float y,
						 float *moveX, float *moveY)
{
	// 変数宣言
	// キャラクタの移動量を足す
	float addX, addY;

	// マップチップ上下左右の座標
	RECT map;

	// キャラクタ座標に移動量を足す
	addX = x + *moveX;
	addY = y + *moveY;

	// ブロックに当たっているかチェック
	if ( GetMapParam(addX, addY) == e_BLOCK )
	{
		// 当たっていた場合、壁から離す
		// ブロックの上下左右の座標を計算
		map.left = ((int)addX / CHIP_SIZE) * CHIP_SIZE;			// 左辺のX座標
		map.right = ((int)addX / CHIP_SIZE + 1) * CHIP_SIZE;	// 右辺のX座標
		map.top = ((int)addY / CHIP_SIZE) * CHIP_SIZE;			// 上辺のY座標
		map.bottom = ((int)addY / CHIP_SIZE + 1) * CHIP_SIZE;	// 下辺のY座標

		// 上辺に衝突 *moveYが0.0fより大きい場合、キャラクタは下に進もうとしている
		if ( *moveY > 0.0f )
		{
			// 移動量を補正
			*moveY = map.top - y - 1.0f;

			// 上辺に衝突したと返す
			return e_HIT_TOP;
		}

		// 下辺に衝突
		if ( *moveY < 0.0f )
		{
			// 移動量を補正
			*moveY = map.bottom - y + 1.0f;

			// 下辺に衝突したと返す
			return e_HIT_BOTTOM;
		}

		// 左辺に衝突
		if ( *moveX > 0.0f )
		{
			// 移動量を補正
			*moveX = map.left - x - 1.0f;

			// 左辺に衝突したと返す
			return e_HIT_LEFT;
		}

		// 右辺に衝突
		if ( *moveX < 0.0f )
		{
			// 移動量を補正
			*moveX = map.right - x + 1.0f;

			// 右辺に衝突したと返す
			return e_HIT_RIGHT;
		}
	}

	// 終了 どこにも当たらなかった
	return 0;
}

// 円のコリジョン
bool Utility::IsCircleCollision(float x1, float y1, int r1,
								float x2, float y2, int r2)
{
	double disX = (double)x2 - (double)x1;
	double disY = (double)y2 - (double)y1;
	double d = sqrt(disX * disX + disY * disY);
	double r = (double)r1 + (double)r2;

	if ( d < r )
	{
		return true;
	}

	return false;
}