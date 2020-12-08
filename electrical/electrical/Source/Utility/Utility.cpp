#include "Utility.h"
#include "../Define/Define.h"

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