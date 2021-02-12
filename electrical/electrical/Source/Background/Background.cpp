#include "DxLib.h"
#include "Background.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

const int BG_GRAPH_SIZE_X = 960;
const int BG_GRAPH_SIZE_Y = 540;

Background::Background()
{
	exRate = (double)WIN_WIDTH / (double)BG_GRAPH_SIZE_X;
}

// •`‰æˆ—
void Background::Draw(float shakeX, float shakeY, int index)
{
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX, WIN_HEIGHT / 2 - (int)shakeY,
				  exRate, 0.0, Graphic::GetInstance()->GetBackground(index), true);
}