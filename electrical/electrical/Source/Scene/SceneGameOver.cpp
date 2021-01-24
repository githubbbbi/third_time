#include "DxLib.h"
#include "SceneGameOver.h"
#include "../Input/InputManager.h"

SceneGameOver::SceneGameOver()
{
}

// 初期化処理
void SceneGameOver::Initialize()
{
	isSceneChange = false;
}

// シーン遷移
void SceneGameOver::SceneChange()
{
	// タイトルへ遷移
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_TITLE;
		isSceneChange = true;
	}
}

// ゲーム終了
void SceneGameOver::GameEnd()
{
	if ( InputManager::IsInputRelease(e_PAUSE) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneGameOver::Update()
{
	SceneChange();
	GameEnd();
}

// 描画処理
void SceneGameOver::Draw()
{
	DrawString(500, 100, "GAMEOVER", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}