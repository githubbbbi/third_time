#include "DxLib.h"
#include "UI_Ready.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

UI_Ready::UI_Ready()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	isReady = true;
}

// 更新処理
void UI_Ready::Update()
{
	if ( !isReady )
	{
		return;
	}

	// 一定時間経過でfalse つまりReadyの処理を終了する
	const int time = 120;
	static int timer = 0;
	if ( timer++ < time )
	{
		return;
	}

	timer = 0;
	isReady = false;
}

// 描画処理
void UI_Ready::Draw()
{
	if ( !isReady )
	{
		return;
	}

	DrawRotaGraph(x, y, 2.0, 0.0,
				  Graphic::GetInstance()->GetUIReady(), true);
}
// isReadyを取得
bool UI_Ready::GetIsReady()
{
	return isReady;
}