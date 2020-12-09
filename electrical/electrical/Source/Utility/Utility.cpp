#include "Utility.h"
#include "../Define/Define.h"
#include <math.h>

// ‰æ–Ê“à‚É‚Æ‚Ç‚Ü‚é
void Utility::StayOnScreen(int *x, int *y, int radius,
						   bool isStayX, bool isStayY)
{
	if ( isStayX )
	{
		if ( *x - radius < 0 )
		{
			*x = 0 + radius;
		}
		else if ( *x + radius > WIN_WIDTH )
		{
			*x = WIN_WIDTH - radius;
		}
	}

	if ( isStayY )
	{
		if ( *y - radius < 0 )
		{
			*y = 0 + radius;
		}
		else if ( *y + radius > WIN_HEIGHT )
		{
			*y = WIN_HEIGHT - radius;
		}
	}
}

// ‰~‚ÌƒRƒŠƒWƒ‡ƒ“
bool Utility::CircleCollision(int x1, int y1, int r1,
							  int x2, int y2, int r2)
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