#include "DxLib.h"
#include "UI_ManipulationMethod.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"
#include "../Input/InputManager.h"

UI_ManipulationMethod::UI_ManipulationMethod()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	graphIndex = 0;
}

// 更新処理
void UI_ManipulationMethod::Update(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		return;
	}

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
}

// 描画処理
void UI_ManipulationMethod::Draw(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		return;
	}

	DrawRotaGraph(x, y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUIManipulationMethod(graphIndex), true);
}