#pragma once

// �w�i�摜�T�C�Y
extern const int BG_GRAPH_SIZE_X;
extern const  int BG_GRAPH_SIZE_Y;

class Background
{
private:
	double exRate;	// �g�嗦

public:
	Background();
	~Background() = default;

	// �`�揈��
	void Draw(float shakeX, float shakeY,int index);
};