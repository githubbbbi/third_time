#include "DxLib.h"
#include "UI_Title.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

UI_Title::UI_Title()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2 + WIN_HEIGHT / 4;
	trasparency = 255;
}

// çXêVèàóù
void UI_Title::Update(bool isBlinking, bool isFlashing)
{
	// ñæñ≈
	if ( isBlinking )
	{
		static int transSpeed = 4;
		trasparency += transSpeed;
		if ( trasparency < 0 || trasparency > 255 )
		{
			transSpeed *= -1;
		}

		return;
	}

	// ì_ñ≈
	if ( isFlashing )
	{
		const int change = 10;
		static int timer = 0;
		timer++;
		trasparency = 255;
		if ( timer < change )
		{
			trasparency = 0;
		}
		else if ( timer > change * 2 )
		{
			timer = 0;
		}
	}
}

// ï`âÊèàóù
void UI_Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trasparency);
	DrawRotaGraph(x, y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUITitle(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}