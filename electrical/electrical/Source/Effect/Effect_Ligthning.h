#pragma once

class Effect_Lightning
{
private:
	// ‚±‚±««««‚É•Ï”éŒ¾


public:
	Effect_Lightning(int x1, int y1, int x2, int y2);
	~Effect_Lightning() = default;

	// ”ò‹——£
	bool IsLengthOver();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw();
};