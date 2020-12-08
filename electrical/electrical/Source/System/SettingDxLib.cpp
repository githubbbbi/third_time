#include "DxLib.h"
#include "SettingDxLib.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"

bool DxLibInit()
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x0, 0x00);

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// DxLibの初期化
	if ( DxLib_Init() == -1 )
	{
		// 異常終了
		return false;
	}

	// 正常終了
	return true;
}

bool DxLibGameLoop()
{
	// (ダブルバッファ)裏面
	ScreenFlip();

	// 20ミリ秒待機(疑似60FPS)
	WaitTimer(20);

	// Windowsシステムからくる情報を処理する
	if ( ProcessMessage() == -1 )
	{
		return false;
	}

	// ESCキーが押されたらループから抜ける
	if ( IsKeyInputRelease(KEY_INPUT_ESCAPE) )
	{
		return false;
	}

	// 画面クリア
	ClearDrawScreen();

	return true;
}