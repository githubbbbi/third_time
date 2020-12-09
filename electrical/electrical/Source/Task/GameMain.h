#pragma once

#include "../Character/Chara_Manager.h"

class GameMain
{
private:
	Chara_Manager *charaManager;

public:
	// コンストラクタ
	GameMain();

	// デストラクタ
	~GameMain();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 終了処理
	void Finalize();
};