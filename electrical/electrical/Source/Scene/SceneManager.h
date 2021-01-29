#pragma once

#include <iostream>
#include "SceneBase.h"

class SceneManager
{
private:
	std::unique_ptr<SceneBase> nowScene;	// 現在処理を行っているシーン
	Scene scene;							// 現在のシーン

	bool isSCPossible;	// シーン遷移可能フラグ

	// フェードイン
	bool FadeIn();

	// フェードアウト
	bool FadeOut();

	// シーン遷移
	void SceneChange();

public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	// ゲーム終了
	bool GetIsGameEnd();
};