#pragma once

class Utility
{
private:
	Utility();

public:
	// マップとの当たり判定


	// 画面内にとどまる
	static void StayOnScreen(int *x, int *y, int radius,
							 bool isStayX, bool isStayY);

	// 円のコリジョン
	static bool CircleCollision(int x1, int y1, int r1,
						 int x2, int y2, int r2);
};