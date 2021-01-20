#pragma once

#include "SceneBase.h"
#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"

class SceneGame:public SceneBase
{
private:
	Chara_Manager *charaManager;
	Stage *stage;
	EffectManager *effects;

	int scrollX, scrollY;	// スクロール量
	int screenX, screenY;	// スクリーン中心座標

	// スクリーン座標を求める
	void Screen();

	// エフェクト管理
	// 「Local」はEffectManagerクラスと名前が被らないよう
	void LocalEffectManager();

	// シーン遷移
	void SceneChange();

	// ゲーム終了
	void GameEnd();

public:
	// コンストラクタ
	SceneGame();

	// デストラクタ
	~SceneGame();

	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

	// 終了処理
	void Finalize();
};