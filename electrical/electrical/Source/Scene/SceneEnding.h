#pragma once

#include "SceneBase.h"

class SceneEnding:public SceneBase
{
private:
	int x;	// 中心座標
	int y;	// 中心座標

	// シーン遷移
	void SceneChange();

	// ゲーム終了
	void GameEnd();

public:
	SceneEnding();
	~SceneEnding() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};