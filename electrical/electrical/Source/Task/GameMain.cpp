#include "DxLib.h"
#include "GameMain.h"
#include "../Input/InputKey.h"


// コンストラクタ
GameMain::GameMain()
{

}

// デストラクタ
GameMain::~GameMain()
{

}

// 初期化処理
void GameMain::Initialize()
{

}

// 更新処理
void GameMain::Update()
{
	// キーボード
	InputKey::KeyUpdate();


}

// 描画処理
void GameMain::Draw()
{
	DrawString(500, 300, "ゲーム画面", GetColor(255, 255, 255));
}

// 終了処理
void GameMain::Finalize()
{

}