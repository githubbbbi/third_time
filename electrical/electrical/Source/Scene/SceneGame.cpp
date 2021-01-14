#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Input/InputManager.h"

// コンストラクタ
SceneGame::SceneGame()
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
SceneGame::~SceneGame()
{
	delete charaManager;
	delete stage;
	delete effects;
}

// 初期化処理
void SceneGame::Initialize()
{
	// キャラクター
	charaManager->Initialize();

	isSceneChange = false;
}

// エフェクト管理
void SceneGame::LocalEffectManager()
{
	// エネミーの死亡エフェクト
	if ( charaManager->GetIsEnemyDeath() )
	{
		// シェイク
		effects->Shake();

		// 爆発
		effects->Explosion(charaManager->GetExplosionPosX(),
						   charaManager->GetExplosionPosY());
	}

	// エフェクト
	effects->Update();
}

// シーン遷移
void SceneGame::SceneChange()
{
	// テスト用
	/*if ( InputManager::IsInputRelease(e_START) )
	{
		isSceneChange = true;
	}*/
}

// ゲーム終了
void SceneGame::GameEnd()
{
	// テスト用
	if ( InputManager::IsInputRelease(e_PAUSE) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneGame::Update()
{
	// エフェクト
	LocalEffectManager();

	// スクロール
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// ステージ
	stage->Update();

	// キャラクター
	charaManager->Update();

	// シーン遷移
	SceneChange();

	// ゲーム終了
	GameEnd();
}

// 描画処理
void SceneGame::Draw()
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
	effects->Draw(scrollX, scrollY);
}

// 終了処理
void SceneGame::Finalize()
{

}