#pragma once

#include "SceneBase.h"
#include <vector>
#include "../Effect/Effect_Ligthning.h"

class SceneTitle:public SceneBase
{
private:
	std::vector<Effect_Lightning *> lightnings;

	// ライトニング更新処理
	void LightningUpdate();

	// ライトニング描画処理
	void LightningDraw();

	// シーン遷移
	void SceneChange();

	// ゲーム終了
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle();

	void Initialize() override;
	void Update() override;
	void Draw() override;
};