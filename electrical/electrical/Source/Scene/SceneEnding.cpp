#include "DxLib.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"

SceneEnding::SceneEnding()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
}

// 初期化処理
void SceneEnding::Initialize()
{
	isSceneChange = false;
}

// シーン遷移
void SceneEnding::SceneChange(bool isSCPossible)
{
	// シーン遷移が可能
	if ( !isSCPossible )
	{
		return;
	}

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
void SceneEnding::Update(bool isSCPossible)
{
	SceneChange(isSCPossible);
	GameEnd();
}

// 描画処理
void SceneEnding::Draw()
{
	DrawRotaGraph(x, y, 2.0, 0.0,
				  Graphic::GetInstance()->GetEnding(), true);
}