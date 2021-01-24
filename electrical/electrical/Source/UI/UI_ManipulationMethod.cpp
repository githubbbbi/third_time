#include "DxLib.h"
#include "UI_ManipulationMethod.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

UI_ManipulationMethod::UI_ManipulationMethod()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT - 100;
}

// •`‰æˆ—
void UI_ManipulationMethod::Draw()
{
	DrawRotaGraph(x, y, 1.0, 0.0, 
				  Graphic::GetInstance()->GetUIManipulationMethod(), true);
}