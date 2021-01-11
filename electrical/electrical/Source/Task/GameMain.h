#pragma once

#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"

class GameMain
{
private:
	Chara_Manager *charaManager;
	Stage *stage;
	EffectManager *effects;

	int backgroundGH;			// 背景画像
	int scrollX, scrollY;		// スクロール量

	// エフェクト管理
	// 「Local」はEffectManagerクラスと名前が被らないよう
	void LocalEffectManager();

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