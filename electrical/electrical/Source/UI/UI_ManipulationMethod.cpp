#include "DxLib.h"
#include "UI_ManipulationMethod.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"
#include "../Input/InputManager.h"

UI_ManipulationMethod::UI_ManipulationMethod()
{
	ui[0] = { 100, WIN_HEIGHT - 25, 0 };
	ui[1] = { WIN_WIDTH / 2, WIN_HEIGHT / 2, 0 };
}

// 更新処理
void UI_ManipulationMethod::Update(bool isDrawUIMM)
{
	// 操作一覧描画フラグ
	if ( !isDrawUIMM )
	{
		// ヘルプ
		// 入力がキーボードの場合
		if ( InputManager::GetIsInputKey() )
		{
			ui[0].graphIndex = 0;
		}
		// パッドの場合
		else if ( InputManager::GetIsInputPad() )
		{
			ui[0].graphIndex = 1;
		}

		return;
	}

	// 操作一覧
	// 入力がキーボードの場合
	if ( InputManager::GetIsInputKey() )
	{
		ui[1].graphIndex = 0;
	}
	// パッドの場合
	else if ( InputManager::GetIsInputPad() )
	{
		ui[1].graphIndex = 1;
	}
}

// 描画処理
void UI_ManipulationMethod::Draw(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		// ヘルプ
		DrawRotaGraph(ui[0].x, ui[0].y, 1.0, 0.0,
					  Graphic::GetInstance()->GetUIHelp(ui[0].graphIndex), true);

		return;
	}

	// 操作一覧
	DrawRotaGraph(ui[1].x, ui[1].y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUIManipulationMethod(ui[1].graphIndex), true);
}