#pragma once

enum Scene
{
	e_NONE,
	e_TITLE,		// タイトル
	e_GAME,			// ゲーム
	e_GAMEOVER,		// ゲームオーバー
	e_ENDING,		// エンディング
};

class SceneBase
{
protected:
	Scene nextScene;	// 次のシーン
	bool isSceneChange;	// シーン遷移フラグ
	bool isGameEnd;		// ゲーム終了フラグ

public:
	SceneBase();
	virtual ~SceneBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Scene GetNextScene();
	bool GetIsSceneChange();
	bool GetIsGameEnd();
};