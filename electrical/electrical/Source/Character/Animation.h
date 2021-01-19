#pragma once

class Animation
{
private:
	int index;
	int waitTime;

public:
	Animation();
	~Animation() = default;

	int AnimationLoop(const int *motion, const int state, int wait, int num);
};