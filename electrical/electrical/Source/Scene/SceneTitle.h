#pragma once

#include "SceneBase.h"

class SceneTitle:public SceneBase
{
private:
	// ここ↓↓↓↓に変数宣言(書き終わったら消していいよ)


	// ライティング更新処理
	void LightingUpdate();
	
	// ライティング描画処理
	void LightingDraw();

	// シーン遷移
	void SceneChange();

	// ゲーム終了
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};