#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

// 初期化処理
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ライトニング更新処理
void SceneTitle::LightningUpdate()
{
	// 最大生成数50個
	int wallX1 = 170;
	int wallY1 = 150;
	int wallX2 = 760;
	int wallY2 = 250;
	if ( lightnings.size() <= 50 )
	{
		// 1フレーム3個
		for ( int i = 0; i < 3; i++ )
		{
			lightnings.push_back(new Effect_Lightning(wallX1, wallY1, wallX2, wallY2));
		}
	}

	// 更新
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Update();
	}

	// 消去
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		if ( lightnings[i]->IsLengthOver() )
		{
			delete lightnings[i];
			lightnings.erase(lightnings.begin() + i);
		}
	}
}

// ライトニング描画処理
void SceneTitle::LightningDraw()
{
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}
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
	LightningUpdate();
	SceneChange();
	GameEnd();
}

// 描画処理
void SceneTitle::Draw()
{
	LightningDraw();
	//DrawString(500, 100, "TITLE", GetColor(255, 255, 255));
	//DrawString(500, 200, "space", GetColor(255, 255, 255));
}