#include "DxLib.h"
#include "UI_Title.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"
#include "../Input/InputManager.h"

UI_Title::UI_Title()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2 + WIN_HEIGHT / 4;
	trasparency = 255;
	graphIndex = 1;
}

// 更新処理
void UI_Title::Update(bool isBlinking, bool isFlashing)
{
	// 入力がキーボードの場合
	if ( InputManager::GetIsInputKey() )
	{
		graphIndex = 0;
	}
	// パッドの場合
	else if ( InputManager::GetIsInputPad() )
	{
		graphIndex = 1;
	}

	// 明滅
	if ( isBlinking )
	{
		static int transSpeed = 4;
		trasparency += transSpeed;
		if ( trasparency < 0 || trasparency > 255 )
		{
			transSpeed *= -1;
		}
	}
	// 点滅
	else if ( isFlashing )
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

// 描画処理
void UI_Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trasparency);
	DrawRotaGraph(x, y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUITitle(graphIndex), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}