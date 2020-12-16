#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
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
	// キーボード
	InputKey::Update();

	// パッド
	InputPad::Update();

	// キャラクター
	charaManager->Update(&shakeAddX, &shakeAddY);

	// ステージ
	stage->Update();

	// シェイク
	Utility::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddX);
}

// 描画処理
void GameMain::Draw()
{
	// 背景
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX, WIN_HEIGHT / 2 - (int)shakeY,
				  1.0, 0.0, backgroundGH, true);

	// キャラクター
	charaManager->Draw(shakeX, shakeY);

	// ステージ
	stage->Draw(shakeX, shakeY);

	// デバッグ用
	DrawFormatString(0, 100, GetColor(255, 255, 255), "shakeAddX:%.2f", shakeAddX);
}

// 終了処理
void GameMain::Finalize()
{

}