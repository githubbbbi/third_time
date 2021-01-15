#include "Animation.h"

Animation::Animation()
{
	index = 0;
	waitTime = 0;
}

int Animation::AnimationLoop(const int motion[], int wait, int num)
{
	if ( ++waitTime >= wait )
	{
		index++;
		index %= num;
		waitTime = 0;
	}

	return motion[index];
}