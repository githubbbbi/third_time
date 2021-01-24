#pragma once

#include <iostream>
#include "SceneBase.h"

class SceneManager
{
private:
	std::unique_ptr<SceneBase> nowScene;	// 現在処理を行っているシーン
	Scene scene;							// 現在のシーン

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