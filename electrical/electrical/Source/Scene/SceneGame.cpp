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
	stage = new Stage;

	// エフェクト
	effects = new EffectManager;

	// UI
	ui = new UI_Manager;

	scrollX = 0;
	scrollY = 0;
	screenX = 0;
	screenY = 0;
	isScroll = false;
	isDrawUIMM = false;

	r = g = b = 255.0f;
	h = s = v = 255.0f;
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

// UI管理
void SceneGame::LoaclUIManager()
{
	// 更新処理
	ui->Update(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);

	// 操作一覧表示中は後ろの明度を下げる
	if ( !isDrawUIMM )
	{
		h = 0.0f;
		s = 0.0f;
		v = 255.0f;
	}
	else
	{
		h = 0.0f;
		s = 0.0f;
		v = 64.0f;
	}

	// ヘルプ(操作一覧を表示)
	if ( !isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		isDrawUIMM = true;
		return;
	}

	// ヘルプを閉じる
	if ( isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		isDrawUIMM = false;
		return;
	}
}

// シーン遷移
void SceneGame::SceneChange()
{
	// プレイヤーが死亡→初期化処理
	if ( !characters->GetPlayerIsAlive() )
	{
		nextScene = e_GAME;
		isSceneChange = true;
		return;
	}

	// プレイヤーがゴール→エンディング
	if ( characters->GetPlayerIsGoal() )
	{
		// 一定時間経過
		static int timer = 0;
		if ( timer++ < 30 )
		{
			return;
		}

		timer = 0;
		nextScene = e_ENDING;
		isSceneChange = true;
		return;
	}
}

// ゲーム終了
void SceneGame::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneGame::Update()
{
	// スクリーン座標を求める
	Screen();

	// 操作一覧表示中は更新処理を行わない
	if ( !isDrawUIMM )
	{
		// スクロール
		Utility::Scroll((int)characters->GetScrollCenterX(),
						(int)characters->GetScrollCenterY(),
						&scrollX, &scrollY, &isScroll);

		// エフェクト
		LocalEffectManager();

		// スクロール中は更新処理を行わない
		if ( !isScroll )
		{
			// キャラクター
			characters->Update(screenX, screenY);

		}
	}

	// UI
	LoaclUIManager();

	// HSVからRGBへ変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);

	// シーン遷移
	SceneChange();

	// ゲーム終了
	GameEnd();
}

// 描画処理
void SceneGame::Draw()
{
	SetDrawBright((int)r, (int)g, (int)b);
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
	SetDrawBright(255, 255, 255);

	// UI
	ui->Draw(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);
}

// 終了処理
void SceneGame::Finalize()
{

}