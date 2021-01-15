#pragma once

#include <iostream>
#include "SceneBase.h"

class SceneManager
{
private:
	// 現在のシーン
	std::unique_ptr<SceneBase> nowScene;
	Scene scene;

	// シーン遷移
	void SceneChange();

public:
	SceneManager();
	~SceneManager() = default;

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	// ゲーム終了
	bool GetIsGameEnd();
};