#pragma once

class Animation
{
private:
	int index;
	int waitTime;

public:
	Animation();
	~Animation() = default;

	int AnimationLoop(const int motion[], int wait, int num);
};