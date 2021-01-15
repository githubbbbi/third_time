#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"
#include "../Resource/Graphic.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	Graphic::Load();

	// マスクセット
	Mask::SetMask();
}

// 初期化処理
void SceneManager::Initialize()
{
	nowScene->Initialize();
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

// シーン遷移
void SceneManager::SceneChange()
{
	if ( !nowScene->GetIsSceneChange() )
	{
		return;
	}

	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneGame);
			scene = e_GAME;
			break;

		case e_GAME:
			nowScene.reset(new SceneTitle);
			scene = e_TITLE;
			break;

		case e_ENDING:
			//nowScene.reset(new SceneTitle);
			//scene = e_TITLE;
			break;
	}
}

// ゲーム終了
bool SceneManager::GetIsGameEnd()
{
	return nowScene->GetIsGameEnd();
}