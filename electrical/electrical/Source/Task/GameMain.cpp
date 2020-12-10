#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"


// コンストラクタ
GameMain::GameMain()
{
	charaManager = nullptr;
}

// デストラクタ
GameMain::~GameMain()
{
	delete charaManager;
}

// 初期化処理
void GameMain::Initialize()
{
	// キャラクターインスタンス生成
	charaManager = new Chara_Manager;

	// キャラクター
	charaManager->Initialize();
}

// 更新処理
void GameMain::Update()
{
	// キーボード
	InputKey::Update();

	// パッド
	InputPad::Update();

	// キャラクター
	charaManager->Update();
}

// 描画処理
void GameMain::Draw()
{
	// キャラクター
	charaManager->Draw();
}

// 終了処理
void GameMain::Finalize()
{

}