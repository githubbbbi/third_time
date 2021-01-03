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
	// 変数宣言
	// キャラクタの移動量を足す
	float addX, addY;

	// マップチップ上下左右の座標
	RECT map;

	// 座標に移動量を足す
	addX = x + *moveX;
	addY = y + *moveY;

	// ブロックに当たっているかチェック
	if ( Stage::GetMapParam(addX, addY) == e_MAP_BLOCK )
	{
		// 当たっていた場合、壁から離す
		// ブロックの上下左右の座標を計算
		map.left = ((int)addX / CHIP_SIZE) * CHIP_SIZE;			// 左辺のX座標
		map.right = ((int)addX / CHIP_SIZE + 1) * CHIP_SIZE;	// 右辺のX座標
		map.top = ((int)addY / CHIP_SIZE) * CHIP_SIZE;			// 上辺のY座標
		map.bottom = ((int)addY / CHIP_SIZE + 1) * CHIP_SIZE;	// 下辺のY座標

		// 上辺に衝突 *moveYが0.0fより大きい場合、下に進もうとしている
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
			*moveX = 0.0f;

			// 左辺に衝突したと返す
			return e_HIT_LEFT;
		}

		// 右辺に衝突
		if ( *moveX < 0.0f )
		{
			// 移動量を補正
			*moveX = 0.0f;

			// 右辺に衝突したと返す
			return e_HIT_RIGHT;
		}
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

// シェイク
void Utility::Shake(float *shakeX, float *shakeY,
					float *addX, float *addY)
{
	// X方向
	*shakeX = (rand() % ((int)*addX - ((int)-*addX) + 1)) + (-*addX);

	if ( *addX > 0 )
	{
		*addX -= SHAKE_DECREASE;
	}

	if ( *addX < 0 )
	{
		*addX = 0;
	}

	// Y方向
	*shakeY = (rand() % ((int)*addY - ((int)-*addY) + 1)) + (-*addY);

	if ( *addY > 0 )
	{
		*addY -= SHAKE_DECREASE;
	}

	if ( *addY < 0 )
	{
		*addY = 0;
	}
}

// スクロール
void Utility::Scroll(int centerX, int centerY, int *scrollX, int *scrollY)
{
	// 指定座標を中心にスクロール量を決定
	*scrollX = centerX - WIN_WIDTH / 2;
	*scrollY = centerY - WIN_HEIGHT / 2;

	// X方向
	// マップの左端より左にはいかない
	if ( *scrollX < 0 )
	{
		*scrollX = 0;
	}

	// マップの右端より右にはいかない
	if ( *scrollX + WIN_WIDTH > MAP_COUNT_X * CHIP_SIZE )
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
	if ( *scrollY + WIN_HEIGHT > MAP_COUNT_Y * CHIP_SIZE )
	{
		*scrollY = MAP_COUNT_Y * CHIP_SIZE - WIN_HEIGHT;
	}
}