#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"


// コンストラクタ
GameMain::GameMain()
{
	
}

// デストラクタ
GameMain::~GameMain()
{
	delete player;
}

// 初期化処理
void GameMain::Initialize()
{
	// プレイヤー生成
	int playerGH = LoadGraph("Resource/Graphic/player.png");
	player = new CharacterPlayer(WIN_WIDTH / 2, WIN_HEIGHT / 2, 5,
								 32, playerGH);
}

// 更新処理
void GameMain::Update()
{
	// キーボード
	InputKey::KeyUpdate();

	// パッド
	InputPad::PadUpdate();

	// プレイヤー
	player->Update();
}

// 描画処理
void GameMain::Draw()
{
	// プレイヤー
	player->Draw();
}

// 終了処理
void GameMain::Finalize()
{

}