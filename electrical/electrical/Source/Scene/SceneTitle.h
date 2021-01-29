#pragma once

#include "SceneBase.h"
#include <vector>
#include "../Effect/Effect_Ligthning.h"
#include "../UI/UI_Title.h"

class SceneTitle:public SceneBase
{
private:
	std::vector<Effect_Lightning *> lightnings;
	UI_Title *ui;

	int x;		// 中心座標
	int y;		// 中心座標
	int width;	// 横幅
	int height;	// 縦幅

	// ライトニング更新処理
	void LightningUpdate();

	// ライトニング描画処理
	void LightningDraw();

	// シーン遷移
	void SceneChange(bool isSCPossible);

	// ゲーム終了
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle();

	void Initialize() override;
	void Update(bool isSCPossible) override;
	void Draw() override;
};