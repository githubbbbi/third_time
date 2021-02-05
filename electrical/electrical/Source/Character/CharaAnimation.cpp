#include "CharaAnimation.h"

CharaAnimation::CharaAnimation()
{
	index = 0;
	waitTime = 0;
}

int CharaAnimation::AnimationLoop(const int *motion, const int state,
								  int wait, int num)
{
	if ( ++waitTime >= wait )
	{
		index++;
		index %= num;
		waitTime = 0;
	}

	return motion[state * num + index];
}