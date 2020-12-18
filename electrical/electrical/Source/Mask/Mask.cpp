#include "DxLib.h"
#include "Mask.h"
#include "../Define/Define.h"

// 変数初期化
int Mask::graphHandle = -1;
int Mask::screenHandle = -1;

double Mask::sizeRate = 0.0;

// マスクのセット
void Mask::SetMask()
{
	// マスク画像
	graphHandle = LoadGraph("Resource/Graphic/Mask/mask.png");

	// アルファチャンネル付きの描画対象グラフィックハンドルを作成
	screenHandle = MakeScreen(WIN_WIDTH, WIN_HEIGHT, TRUE);

	// マスク画像のサイズを設定
	sizeRate = 50.0;

	// マスク機能の初期化を行う
	CreateMaskScreen();

	// MakeScreenで作成したグラフィックハンドルをセット
	SetMaskScreenGraph(screenHandle);
}

// マスクの収縮
void Mask::MaskShrink()
{
	if ( sizeRate > 0.0 )
	{
		//sizeRate -= 0.5;
	}
}

// マスクの描画
void Mask::DrawMask()
{
	// マスクの収縮
	MaskShrink();

	// 描画先をマスク用の画像に変更
	SetDrawScreen(screenHandle);

	// マスク用の画像をクリア
	ClearDrawScreen();

	// マスク画像描画
	DrawRotaGraph(WIN_WIDTH / 2, WIN_HEIGHT / 2,
				  sizeRate, 0.0, graphHandle, true);

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	// 裏画面をクリア
	ClearDrawScreen();
}

// マスクの後処理
void Mask::LoopMask()
{
	// マスクを有効にする
	SetUseMaskScreenFlag(TRUE);

	// 画面いっぱいに四角形を描画
	DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);

	// マスクを無効にする
	SetUseMaskScreenFlag(FALSE);
}