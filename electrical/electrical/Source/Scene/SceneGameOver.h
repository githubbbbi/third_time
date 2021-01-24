#pragma once

#include "SceneBase.h"

class SceneGameOver:public SceneBase
{
private:
	// シーン遷移
	void SceneChange();

	// ゲーム終了
	void GameEnd();

public:
	SceneGameOver();
	~SceneGameOver() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};