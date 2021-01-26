#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneTitle::SceneTitle()
{
}

// 初期化処理
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ライティング更新処理
void SceneTitle::LightingUpdate()
{

}

// ライティング描画処理
void SceneTitle::LightingDraw()
{

}

// シーン遷移
void SceneTitle::SceneChange()
{
	// メインゲームへ遷移
	if ( InputManager::IsInputRelease(e_START) )
	{
		nextScene = e_GAME;
		isSceneChange = true;
	}
}

// ゲーム終了
void SceneTitle::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneTitle::Update()
{
	LightingUpdate();
	SceneChange();
	GameEnd();
}

// 描画処理
void SceneTitle::Draw()
{
	LightingDraw();
	DrawString(500, 100, "TITLE", GetColor(255, 255, 255));
	DrawString(500, 200, "space", GetColor(255, 255, 255));
}