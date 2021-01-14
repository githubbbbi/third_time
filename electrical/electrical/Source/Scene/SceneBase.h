#pragma once

enum Scene
{
	e_TITLE,	// タイトル
	e_GAME,		// ゲーム
	e_ENDING,	// エンディング
};

class SceneBase
{
protected:
	bool isSceneChange;
	bool isGameEnd;

public:
	SceneBase();
	~SceneBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool GetIsSceneChange();
	bool GetIsGameEnd();
};