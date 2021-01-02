#pragma once

#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"

class GameMain
{
private:
	Chara_Manager *charaManager;
	Stage *stage;

	int backgroundGH;			// 背景画像
	float shakeX, shakeY;		// シェイク
	float shakeAddX, shakeAddY;	// シェイク量
	int scrollX, scrollY;		// スクロール量

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