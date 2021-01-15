#include "DxLib.h"
#include <time.h>
#include "System.h"
#include "SettingDxLib.h"

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
	if ( !SettingDxLib::DxLibInit() )
	{
		return false;
	}

	// シード値
	srand((unsigned)time(nullptr));

	// インスタンス生成
	scene = new SceneManager;

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

		/* ----- 描画処理 ----- */
		scene->Draw();

		// ゲーム終了
		if ( scene->GetIsGameEnd() )
		{
			break;
		}

		// DxLibのループ処理
		if ( !SettingDxLib::DxLibGameLoop() )
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