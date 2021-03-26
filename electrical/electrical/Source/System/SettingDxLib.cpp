#include "DxLib.h"
#include "SettingDxLib.h"
#include "../Define/Define.h"
#pragma comment( lib, "winmm.lib" )

// 変数初期化
long long SettingDxLib::baseTime = 0;
int SettingDxLib::refreshRate = 0;
unsigned long long SettingDxLib::frequency = 0;

// 初期化処理
void SettingDxLib::Initialize()
{
	baseTime = GetNowHiPerformanceCount();
	frequency = GetSysPerformanceFrequency();
}

// スリープ
void SettingDxLib::MySleep(int flag)
{
	// flagがFALSE = Sleepを未使用(Vsync使用)
	if ( flag == FALSE )
	{
		return;
	}

	// 1フレームにかけられる最小時間(秒)
	const float FRAME_TIME = 1.0f / (float)refreshRate;

	// 現在時刻を取得(マイクロ秒)
	long long currentTime = GetNowHiPerformanceCount();

	// 経過時間(秒) = (今の時間 - 前フレームの時間) / 周波数
	float frameTime = (float)(currentTime - baseTime) / (float)frequency;

	//処理時間に余裕がある場合はその分待つ
	if ( frameTime < FRAME_TIME )
	{
		//Sleepの時間(ミリ秒)を計算
		DWORD sleepTime = (DWORD)((FRAME_TIME - frameTime) * 1000.0f);

		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);
	}

	baseTime = currentTime;	// 基準時刻を現在時刻に設定
}

// DxLibの初期化処理
bool SettingDxLib::InitDxLib()
{
	int windowMode = TRUE;
	if ( MessageBox(NULL, "フルスクリーンで起動しますか？",
					"起動オプション", MB_YESNO) == IDYES )
	{
		// フルスクリーンモードに設定
		windowMode = FALSE;
	}
	else
	{
		// ウィンドウモードに設定
		windowMode = TRUE;
	}

	// ウィンドウモードを設定
	ChangeWindowMode(windowMode);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// デスクトップの解像度を取得
	int desktopWidth, desktopHeight;
	GetDefaultState(&desktopWidth, &desktopHeight, NULL);

	// リフレッシュレート
	HDC hdc = GetDC(GetMainWindowHandle());			// デバイスコンテキストの取得
	refreshRate = GetDeviceCaps(hdc, VREFRESH);		// リフレッシュレートの取得
	ReleaseDC(GetMainWindowHandle(), hdc);			// デバイスコンテキストの解放

	// 画面サイズの最大サイズ、カラービット数、最大リフレッシュレートを設定(モニターに合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32, refreshRate);

	// 60以上の場合は60に設定(60fpsで固定)
	if ( refreshRate >= 60 )
	{
		refreshRate = 60;
	}

	// 画面サイズを設定(解像度との比率で設定)
	double winExRate = 1.0;
	if ( windowMode == FALSE )
	{
		// フルスクリーン時は拡大
		winExRate = desktopWidth / WIN_WIDTH;
	}

	SetWindowSizeExtendRate(winExRate);

	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 0);

	// 二重起動の設定
	SetDoubleStartValidFlag(FALSE);

	// 垂直同期の設定
	SetWaitVSyncFlag(TRUE);

	// バックグラウンド処理
	SetAlwaysRunFlag(FALSE);

	// ログの出力先を設定
	SetApplicationLogSaveDirectory("./");

	// DxLibの初期化
	if ( DxLib_Init() == -1 )
	{
		// 異常終了
		return false;
	}

	// マウス表示設定
	SetMouseDispFlag(TRUE);

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 初期化処理
	Initialize();

	// 正常終了
	return true;
}

// DxLibの描画処理
bool SettingDxLib::DrawDxLib()
{
	// (ダブルバッファ)裏面
	ScreenFlip();

	// スリープ
	MySleep(TRUE);

	// Windowsシステムからくる情報を処理する
	if ( ProcessMessage() == -1 )
	{
		return false;
	}

	// 画面クリア
	ClearDrawScreen();

	return true;
}