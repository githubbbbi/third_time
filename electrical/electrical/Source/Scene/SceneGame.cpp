#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Input/InputManager.h"
#include "../Background/Background.h"

// コンストラクタ
SceneGame::SceneGame()
{
	// キャラクター
	characters = new Chara_Manager;

	// ステージ
	stage = new Stage();

	// エフェクト
	effects = new EffectManager();

	// UI
	ui = new UI_Manager;

	scrollX = 0;
	scrollY = 0;

	screenX = 0;
	screenY = 0;
}

// デストラクタ
SceneGame::~SceneGame()
{
	delete characters;
	delete stage;
	delete effects;
	delete ui;
}

// 初期化処理
void SceneGame::Initialize()
{
	// ステージ
	if ( !stage->Initialize() )
	{
		isGameEnd = true;
	}

	// キャラクター
	if ( !characters->Initialize() )
	{
		isGameEnd = true;
	}

	isSceneChange = false;
}

// スクリーン座標を求める
void SceneGame::Screen()
{
	screenX = scrollX + WIN_WIDTH / 2;
	screenY = scrollY + WIN_HEIGHT / 2;
}

// エフェクト管理
void SceneGame::LocalEffectManager()
{
	// キャラクターの死亡エフェクト
	if ( characters->GetIsCharaDeath() )
	{
		// シェイク
		effects->Shake();

		// 爆発
		effects->Explosion(characters->GetExplosionPosX(),
						   characters->GetExplosionPosY());
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
	// スクリーン座標を求める
	Screen();

	// エフェクト
	LocalEffectManager();

	// スクロール
	Utility::Scroll((int)characters->GetScrollCenterX(),
					(int)characters->GetScrollCenterY(), &scrollX, &scrollY);

	// ステージ
	stage->Update();

	// キャラクター
	characters->Update(screenX, screenY);

	// UI
	ui->Update(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(), characters->GetPlayerMaxBattery());

	// シーン遷移
	SceneChange();

	// ゲーム終了
	GameEnd();
}

// 描画処理
void SceneGame::Draw()
{
	// 背景
	Background back;
	back.Draw(effects->GetShakeX(), effects->GetShakeY());

	// ステージ
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(),
				scrollX, scrollY, screenX, screenY);

	// キャラクター
	characters->Draw(effects->GetShakeX(),
					 effects->GetShakeY(), scrollX, scrollY);

	// エフェクト
	effects->Draw(scrollX, scrollY);

	// UI
	ui->Draw(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(), characters->GetPlayerMaxBattery());

	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 255, 255), "%d,%d", screenX, screenY);
	DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 20, GetColor(255, 255, 255), "%d,%d", scrollX, scrollY);
}

// 終了処理
void SceneGame::Finalize()
{

}