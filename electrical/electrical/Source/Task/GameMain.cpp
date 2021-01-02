#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"


// コンストラクタ
GameMain::GameMain()
{
	// キャラクターインスタンス生成
	charaManager = new Chara_Manager;

	// ステージインスタンス生成
	int mapGH[e_MAP_KIND_NUM];
	LoadDivGraph("Resource/Graphic/MapChip/mapChip.png",
				 e_MAP_KIND_NUM, e_MAP_KIND_NUM, 1, CHIP_SIZE, CHIP_SIZE, mapGH);
	stage = new Stage(mapGH);

	// 背景
	backgroundGH = LoadGraph("Resource/Graphic/Background/background.png");

	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
	scrollX = 0;
	scrollY = 0;
}

// デストラクタ
GameMain::~GameMain()
{
	delete charaManager;
}

// 初期化処理
void GameMain::Initialize()
{
	// キャラクター
	charaManager->Initialize();

	// シェイク
	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
}

// 更新処理
void GameMain::Update()
{
	// 入力
	InputManager::Update();

	// シェイク
	Utility::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddX);

	// スクロール
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// ステージ
	stage->Update();

	// キャラクター
	charaManager->Update(&shakeAddX, &shakeAddY);
}

// 描画処理
void GameMain::Draw()
{
	// 背景
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX - scrollX, WIN_HEIGHT / 2 - (int)shakeY - scrollY,
				  1.0, 0.0, backgroundGH, true);

	// ステージ
	stage->Draw(shakeX, shakeY, scrollX, scrollY);

	// キャラクター
	charaManager->Draw(shakeX, shakeY, scrollX, scrollY);
}

// 終了処理
void GameMain::Finalize()
{

}