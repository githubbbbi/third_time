#include "DxLib.h"
#include <time.h>
#include "System.h"
#include "SettingDxLib.h"
#include "FrameRate.h"

// コンストラクタ
System::System()
{
	scene = nullptr;
}

// デストラクタ
System::~System()
{
	delete scene;
}

// 初期化処理
bool System::Initialize()
{
	// DXLibの初期化
	if ( !SettingDxLib::InitDxLib() )
	{
		return false;
	}

	// シード値
	srand((unsigned)time(nullptr));

	// インスタンス生成
	scene = new SceneManager;

	// FrameRateの初期化
	FrameRate::Initialize();

	return true;
}

// メインループ
bool System::MainLoop()
{
	// ゲームループ
	while ( true )
	{
		/* ----- 更新処理 ----- */
		scene->Update();

		// FPSの計算
		FrameRate::CalcFPS();

		/* ----- 描画処理 ----- */
		scene->Draw();

		// FPSの表示
		FrameRate::DrawFPS();

		// ゲーム終了
		if ( scene->GetIsGameEnd() )
		{
			break;
		}

		// DxLibの描画処理
		if ( !SettingDxLib::DrawDxLib() )
		{
			return false;
		}
	}

	return true;
}

// 終了処理
void System::Finalize()
{
	scene->Finalize();

	// Dxライブラリ終了処理
	DxLib_End();
}

// メイン処理
bool System::Main()
{
	// 初期化処理
	if ( !Initialize() )
	{
		return false;
	}

	// メインループ処理を行う
	if ( !MainLoop() )
	{
		return false;
	}

	// 終了処理
	Finalize();

	return true;
}