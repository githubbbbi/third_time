#include <stdlib.h>
#include "Effect_Shake.h"

void Effect_Shake::Shake(float *shakeX, float *shakeY,
						 float *addX, float *addY)
{
	// X����
	*shakeX = (rand() % ((int)*addX - ((int)-*addX) + 1)) + (-*addX);

	if ( *addX > 0 )
	{
		*addX -= SHAKE_DECREASE;
	}

	if ( *addX < 0 )
	{
		*addX = 0;
	}

	// Y����
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