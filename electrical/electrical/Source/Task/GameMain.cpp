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

	// エフェクト
	int particleGH = LoadGraph("Resource/Graphic/Effects/particle.png");
	effects = new EffectManager(particleGH);

	scrollX = 0;
	scrollY = 0;
}

// デストラクタ
GameMain::~GameMain()
{
	delete charaManager;
	delete stage;
	delete effects;
}

// 初期化処理
void GameMain::Initialize()
{
	// キャラクター
	charaManager->Initialize();
}

// 更新処理
void GameMain::Update()
{
	// 入力
	InputManager::Update();

	// エフェクト
	effects->Update();

	// エネミーの死亡エフェクト
	if ( charaManager->IsEnemyDeath() )
	{
		effects->Shake();
		//effects->Explosion(charaManager->x, charaManager->);
	}

	// スクロール
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// ステージ
	stage->Update();

	// キャラクター
	charaManager->Update();
}

// 描画処理
void GameMain::Draw()
{
	// 背景
	DrawRotaGraph(WIN_WIDTH / 2 - (int)effects->GetShakeX() - scrollX,
				  WIN_HEIGHT / 2 - (int)effects->GetShakeY() - scrollY,
				  1.0, 0.0, backgroundGH, true);

	// ステージ
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(), scrollX, scrollY);

	// キャラクター
	charaManager->Draw(effects->GetShakeX(),
					   effects->GetShakeY(), scrollX, scrollY);

	// エフェクト
	effects->Draw();
}

// 終了処理
void GameMain::Finalize()
{

}