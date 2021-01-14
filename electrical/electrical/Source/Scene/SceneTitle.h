#pragma once

#include "SceneBase.h"

class SceneTitle:public SceneBase
{
private:
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