#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneEnding.h"
#include "../Input/InputManager.h"
#include "../Mask/Mask.h"
#include "../Resource/Graphic.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneTitle>();
	scene = e_TITLE;

	// 画像の読み込み
	Graphic::GetInstance()->Load();

	// マスクセット
	Mask::SetMask();
}

SceneManager::~SceneManager()
{
	// delete
	nowScene.reset();
}

// 初期化処理
void SceneManager::Initialize()
{
	nowScene->Initialize();
}

// フェードイン
bool SceneManager::FadeIn()
{
	// シーン遷移中にはフェードインは行わない
	if ( nowScene->GetIsSceneChange() )
	{
		return false;
	}

	// マスクの拡大終了
	if ( Mask::MaskScaleUp() )
	{
		return true;
	}

	return false;
}

// フェードアウト
bool SceneManager::FadeOut()
{
	if ( !nowScene->GetIsSceneChange() )
	{
		return false;
	}

	// マスクの縮小終了
	if ( Mask::MaskScaleDown() )
	{
		return true;
	}

	return false;
}

// シーン遷移
void SceneManager::SceneChange()
{
	// フェードアウト後にシーン遷移を行う
	if ( !FadeOut() )
	{
		return;
	}

	// シーン遷移
	scene = nowScene->GetNextScene();

	// 遷移後のシーンを生成し初期化処理を行う(同時に遷移前のシーンも削除も行う)
	switch ( scene )
	{
		case e_TITLE:
			nowScene.reset(new SceneTitle);
			nowScene->Initialize();
			break;

		case e_GAME:
			nowScene.reset(new SceneGame);
			nowScene->Initialize();
			break;

		case e_ENDING:
			nowScene.reset(new SceneEnding);
			nowScene->Initialize();
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

	// フェードイン
	FadeIn();

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