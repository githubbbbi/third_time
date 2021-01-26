#include "DxLib.h"
#include "Mask.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

const double EX_RATE_SPEED = 2.0;
const double MAX_EX_RATE = 200.0;
const double MIN_EX_RATE = 0.0;

// 変数初期化
int Mask::screenHandle = -1;
double Mask::exRate = 0.0;

// マスクのセット
void Mask::SetMask()
{
	// アルファチャンネル付きの描画対象グラフィックハンドルを作成
	screenHandle = MakeScreen(WIN_WIDTH, WIN_HEIGHT, TRUE);

	// マスク画像のサイズを設定
	exRate = MAX_EX_RATE;

	// マスク機能の初期化を行う
	CreateMaskScreen();

	// MakeScreenで作成したグラフィックハンドルをセット
	SetMaskScreenGraph(screenHandle);
}

// マスクの拡大
bool Mask::MaskScaleUp()
{
	if ( exRate < MAX_EX_RATE )
	{
		exRate += EX_RATE_SPEED;
	}
	else if ( exRate >= MAX_EX_RATE )
	{
		exRate = MAX_EX_RATE;
		return true;
	}

	return false;
}

// マスクの縮小
bool Mask::MaskScaleDown()
{
	static int timer = 0;

	if ( exRate > MIN_EX_RATE )
	{
		exRate -= EX_RATE_SPEED;
	}
	else if ( exRate <= MIN_EX_RATE )
	{
		exRate = MIN_EX_RATE;

		// 一定時間経過でtrue
		if ( timer++ > 30 )
		{
			timer = 0;
			return true;
		}
	}

	return false;
}

// マスクの描画
void Mask::DrawMask()
{
	// 描画先をマスク用の画像に変更
	SetDrawScreen(screenHandle);

	// マスク用の画像をクリア
	ClearDrawScreen();

	// マスク画像描画
	DrawRotaGraph(WIN_WIDTH / 2, WIN_HEIGHT / 2,
				  exRate, 0.0, Graphic::GetInstance()->GetMask(), true);

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