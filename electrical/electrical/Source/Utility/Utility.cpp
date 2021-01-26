#include "DxLib.h"
#include <math.h>
#include "Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

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
		else if ( *x + radius > MAP_COUNT_X * CHIP_SIZE )
		{
			*x = (float)(MAP_COUNT_X * CHIP_SIZE) - (float)radius;
		}
	}

	if ( isStayY )
	{
		if ( *y - radius < 0 )
		{
			*y = (float)0 + (float)radius;
		}
		else if ( *y + radius > MAP_COUNT_Y * CHIP_SIZE )
		{
			*y = (float)(MAP_COUNT_Y * CHIP_SIZE) - (float)radius;
		}
	}
}

// マップとの当たり判定
// 1：左辺、2：右辺、3：上辺、4：下辺
int Utility::MapHitCheck(float x, float y,
						 float *moveX, float *moveY)
{
	const float value = 1.0f;

	// 座標に移動量を足す
	float addX = x + *moveX;
	float addY = y + *moveY;

	// ブロックに当たっているかチェック
	if ( Stage::GetMapParam(addX, addY) == e_MAP_BLOCK )
	{
		// 当たっていた場合、壁から離す
		// ブロックの上下左右の座標を計算
		RECT map;
		map.left = ((int)addX / CHIP_SIZE) * CHIP_SIZE;				// 左辺のX座標
		map.right = ((int)addX / CHIP_SIZE + 1) * CHIP_SIZE - 1;	// 右辺のX座標
		map.top = ((int)addY / CHIP_SIZE) * CHIP_SIZE;				// 上辺のY座標
		map.bottom = ((int)addY / CHIP_SIZE + 1) * CHIP_SIZE;		// 下辺のY座標

		// 上辺に衝突 moveYが0.0fより大きい場合、下に進もうとしている
		if ( *moveY > 0.0f )
		{
			// 移動量を補正
			*moveY = (float)map.top - y - value;

			// 上辺に衝突したと返す
			return e_HIT_BLOCK_TOP;
		}

		// 下辺に衝突
		if ( *moveY < 0.0f )
		{
			// 移動量を補正
			*moveY = (float)map.bottom - y + value;

			// 下辺に衝突したと返す
			return e_HIT_BLOCK_BOTTOM;
		}

		// 左辺に衝突
		if ( *moveX > 0.0f )
		{
			// 移動量を補正
			*moveX = (float)map.left - x - value;

			// 左辺に衝突したと返す
			return e_HIT_BLOCK_LEFT;
		}

		// 右辺に衝突
		if ( *moveX < 0.0f )
		{
			// 移動量を補正
			*moveX = (float)map.right - x + value;;

			// 右辺に衝突したと返す
			return e_HIT_BLOCK_RIGHT;
		}
	}

	// ゴールとの判定
	if ( Stage::GetMapParam(addX, addY) == e_MAP_GOAL )
	{
		return e_HIT_GOAL;
	}

	// 終了 どこにも当たらなかった
	return e_HIT_NOT;
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

// 矩形の子リジョン
bool Utility::IsRectCollision(float x1, float y1, int w1, int h1,
							  float x2, float y2, int w2, int h2)
{
	float halfW1 = (float)w1 / 2.0f;
	float halfH1 = (float)h1 / 2.0f;
	float halfW2 = (float)w2 / 2.0f;
	float halfH2 = (float)h2 / 2.0f;

	if ( fabsf(x1 - x2) < halfW1 + halfW2 &&
		fabsf(y1 - y2) < halfH1 + halfH2 )
	{
		return true;
	}

	return false;
}

// スクロール
void Utility::Scroll(int centerX, int centerY,
					 int *scrollX, int *scrollY, bool *isScroll)
{
	// スクロールスピード
	const int scrollSpeedX = 20;
	const int scrollSpeedY = 15;

	// 右スクロールフラグ
	bool isRightScroll = false;

	// 下スクロールフラグ
	bool isBottomScroll = false;

	// フラグ初期化
	*isScroll = false;

	// スクリーン座標より端に行くとスクロール
	// 左スクロール
	if ( *scrollX > (centerX / WIN_WIDTH) * WIN_WIDTH )
	{
		*scrollX -= scrollSpeedX;
		*isScroll = true;
	}
	// 右スクロール
	else if ( *scrollX < (centerX / WIN_WIDTH) * WIN_WIDTH )
	{
		*scrollX += scrollSpeedX;
		*isScroll = true;
		isRightScroll = true;
	}

	// 上スクロース
	if ( *scrollY > (centerY / WIN_HEIGHT) * WIN_HEIGHT )
	{
		*scrollY -= scrollSpeedY;
		*isScroll = true;
	}
	// 下スクロール
	else if ( *scrollY < (centerY / WIN_HEIGHT) * WIN_HEIGHT )
	{
		*scrollY += scrollSpeedY;
		*isScroll = true;
		isBottomScroll = true;
	}


	// 右スクロール＆下スクロースしたときのみ
	// スクロール量をウィンドウサイズの倍数に調整
	// X方向
	if ( isRightScroll )
	{
		int x = *scrollX - (centerX / WIN_WIDTH) * WIN_WIDTH;
		if ( x > 0 )
		{
			*scrollX -= x;
		}
	}

	// Y方向
	if ( isBottomScroll )
	{
		int y = *scrollY - (centerY / WIN_HEIGHT) * WIN_HEIGHT;
		if ( y > 0 )
		{
			*scrollY -= y;
		}
	}

	// X方向
	// マップの左端より左にはいかない
	if ( *scrollX < 0 )
	{
		*scrollX = 0;
	}
	// マップの右端より右にはいかない
	else if ( *scrollX + WIN_WIDTH > MAP_COUNT_X * CHIP_SIZE )
	{
		*scrollX = MAP_COUNT_X * CHIP_SIZE - WIN_WIDTH;
	}

	// Y方向
	// マップの上端より上にはいかない
	if ( *scrollY < 0 )
	{
		*scrollY = 0;
	}
	// マップの下端より下にはいかない
	else if ( *scrollY + WIN_HEIGHT > MAP_COUNT_Y * CHIP_SIZE )
	{
		*scrollY = MAP_COUNT_Y * CHIP_SIZE - WIN_HEIGHT;
	}
}

// HSVからRGBに変換
void Utility::ConvertHSVtoRGB(float *r, float *g, float *b,
							  float h, float s, float v)
{
	float max = v;
	float min = max - (s / 255.0f) * max;

	if ( h >= 0 && h <= 60 )
	{
		*r = max;
		*g = (h / 60.0f) * (max - min) + min;
		*b = min;
	}
	else if ( h <= 120 )
	{
		*r = ((120.0f - h) / 60.0f) * (max - min) + min;
		*g = max;
		*b = min;
	}
	else if ( h <= 180 )
	{
		*r = min;
		*g = max;
		*b = ((h - 120.0f) / 60.0f) * (max - min) + min;
	}
	else if ( h <= 240 )
	{
		*r = min;
		*g = ((240.0f - h) / 60.0f) * (max - min) + min;
		*b = max;
	}
	else if ( h <= 300 )
	{
		*r = ((h - 240.0f) / 60.0f) * (max - min) + min;
		*g = min;
		*b = max;
	}
	else if ( h <= 360 )
	{
		*r = max;
		*g = min;
		*b = ((360.0f - h) / 60.0f) * (max - min) + min;
	}
}