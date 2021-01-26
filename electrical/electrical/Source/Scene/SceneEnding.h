#pragma once

#include "SceneBase.h"

class SceneEnding:public SceneBase
{
private:
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