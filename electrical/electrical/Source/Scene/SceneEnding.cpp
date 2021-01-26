#include "DxLib.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneEnding::SceneEnding()
{
}

// 初期化処理
void SceneEnding::Initialize()
{
	isSceneChange = false;
}

// シーン遷移
void SceneEnding::SceneChange()
{
	// タイトルへ遷移
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_TITLE;
		isSceneChange = true;
	}
}

// ゲーム終了
void SceneEnding::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneEnding::Update()
{
	SceneChange();
	GameEnd();
}

// 描画処理
void SceneEnding::Draw()
{
	DrawString(500, 100, "ENDING", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}