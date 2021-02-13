#include "DxLib.h"
#include "Frame.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"

// •`‰æˆ—
void Frame::Draw()
{
	DrawRotaGraph(WIN_WIDTH / 2, WIN_HEIGHT / 2,
				  1.0, 0.0,
				  Graphic::GetInstance()->GetFrame(), true);
}