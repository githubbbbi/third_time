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
	// 最大生成数50個(wall系は雷反射用のタイトル周りの四角の値)

	//if ( lightnings.size() <= 50 )
	//{
	//	// 1フレーム3個
	//	for ( int i = 0; i < 3; i++ )
	//	{
	//		lightnings.push_back(new Lightning(wallX, wallY, wallX2, wallY2));
	//	}
	//}

	//// 更新　初期化
	//for ( unsigned int i = 0; i < lightnings.size(); i++ )
	//{
	//	lightnings[i]->Initialize();
	//	lightnings[i]->Update();
	//}

	//// 消去(is付いてないないや　ごめん）
	//for ( int i = lightnings.size() - 1; i >= 0; i-- )
	//{
	//	if ( lightnings[i]->LengthOver() )
	//	{
	//		delete lightnings[i];
	//		lightnings.erase(lightnings.begin() + i);
	//	}
	//}
}

// ライティング描画処理
void SceneTitle::LightingDraw()
{
	// 雷
	/*for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}*/
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