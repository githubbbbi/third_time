#pragma once

#include "SceneBase.h"
#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"
#include "../UI/UI_Manager.h"

class SceneGame:public SceneBase
{
private:
	Chara_Manager *characters;
	Stage *stage;
	EffectManager *effects;
	UI_Manager *ui;

	int scrollX, scrollY;	// スクロール量
	int screenX, screenY;	// スクリーン中心座標
	bool isScroll;			// スクロールフラグ
	bool isDrawUIMM;		// 操作方法UI描画フラグ

	float r;		// 赤色				:0~255
	float g;		// 緑色				:0~255
	float b;		// 青色				:0~255
	float h;		// 色相(hue)			:0~360
	float s;		// 彩度(saturation)	:0~255
	float v;		// 明度(value)		:0~255

	// スクリーン座標を求める
	void Screen();

	// エフェクト管理
	void MyEffectManager();

	// UI管理
	void LoaclUIManager();

	// シーン遷移
	void SceneChange(bool isSCPossible);

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
	void Update(bool isSCPossible) override;

	// 描画処理
	void Draw() override;

	// 終了処理
	void Finalize();
};