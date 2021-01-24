#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"
#include "../Resource/Graphic.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	Graphic::GetInstance()->Load();

	// マスクセット
	Mask::SetMask();
}

// 初期化処理
void SceneManager::Initialize()
{
	nowScene->Initialize();
}

// シーン遷移
void SceneManager::SceneChange()
{
	if ( !nowScene->GetIsSceneChange() )
	{
		return;
	}

	// シーン遷移
	switch ( scene )
	{
		case e_TITLE:
			scene = nowScene->GetNextScene();
			break;

		case e_INITIALIZE:
			// 初期化処理後はゲーム
			nowScene.reset(new SceneGame);
			nowScene->Initialize();
			scene = e_GAME;
			break;

		case e_GAME:
			scene = nowScene->GetNextScene();
			break;

		case e_GAMEOVER:
			// タイトルに戻る
			//scene = nowScene->GetNextScene();
			break;

		case e_ENDING:
			//nowScene.reset(new SceneTitle);
			//scene = nowScene->GetNextScene();
			break;

		default:
			break;
	}

	// シーンを生成
	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneTitle);
			break;

		case e_GAME:
			// ゲームシーンはシーン遷移の初期化シーンで行っているので
			// ここでは行わない
			break;

		case e_GAMEOVER:
			nowScene.reset(new SceneGameOver);
			break;

		case e_ENDING:
			//nowScene.reset(new SceneEnding);
			break;

		default:
			break;
	}
}

// 更新処理
void SceneManager::Update()
{
	// 入力
	InputManager::Update();

	// 現在のシーン
	nowScene->Update();

	// シーン遷移
	SceneChange();
}

// 描画処理
void SceneManager::Draw()
{
	// マスクの描画
	Mask::DrawMask();

	// 現在のシーン
	nowScene->Draw();

	// マスクの後処理
	Mask::LoopMask();
}

// 終了処理
void SceneManager::Finalize()
{
	// 画像解放
	Graphic::GetInstance()->Release();
}

// ゲーム終了
bool SceneManager::GetIsGameEnd()
{
	return nowScene->GetIsGameEnd();
}