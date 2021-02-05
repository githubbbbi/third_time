#include "DxLib.h"
#include "SettingDxLib.h"
#include "../Define/Define.h"

bool SettingDxLib::DxLibInit()
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// アイコンを設定
	SetWindowIconID(634);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x0, 0x00);

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 垂直同期をオフ
	SetWaitVSyncFlag(FALSE);

	// DxLibの初期化
	if ( DxLib_Init() == -1 )
	{
		// 異常終了
		return false;
	}

	// 正常終了
	return true;
}

bool SettingDxLib::DxLibGameLoop()
{
	// (ダブルバッファ)裏面
	ScreenFlip();

	// 16ミリ秒待機(疑似60FPS)
	WaitTimer(16);

	// Windowsシステムからくる情報を処理する
	if ( ProcessMessage() == -1 )
	{
		return false;
	}

	return true;
}