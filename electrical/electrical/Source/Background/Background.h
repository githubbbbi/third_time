#pragma once

// ”wŒi‰æ‘œƒTƒCƒY
extern const int BG_GRAPH_SIZE_X;
extern const  int BG_GRAPH_SIZE_Y;

class Background
{
private:
	double exRate;	// Šg‘å—¦

public:
	Background();
	~Background() = default;

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY,int index);
};