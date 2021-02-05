#pragma once

class CharaAnimation
{
private:
	int index;
	int waitTime;

public:
	CharaAnimation();
	~CharaAnimation() = default;

	int AnimationLoop(const int *motion, const int state,
					  int wait, int num);
};