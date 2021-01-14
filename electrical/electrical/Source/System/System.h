#pragma once

#include "../Scene/SceneManager.h"

class System
{
private:
	SceneManager *scene;

public:
	// コンストラクタ
	System();

	// デストラクタ
	~System();

	// メイン処理
	bool Main();

	// 初期化処理
	bool Initialize();

	// メインループ
	bool MainLoop();

	// 終了処理
	void Finalize();
};