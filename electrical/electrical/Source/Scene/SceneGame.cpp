#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Utility/Frame.h"
#include "../Input/InputManager.h"
#include "../Background/Background.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

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

	// レターボックス
	for ( int i = 0; i < 4; i++ )
	{
		letterBox[i] = { 0, 0, 0, 0,
						 0.0f, 0.0f, 0.0f,
						 0.0f, 0.0f, 0.0f };
	}

	scrollX = 0;
	scrollY = 0;
	screenX = 0;
	screenY = 0;
	displaceX = 0.0f;
	displaceY = 0.0f;
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

// スクリーン座標の初期化処理
void SceneGame::InitScreenPos()
{
	// スクリーンの中心となるキャラクターの座標
	int charaX = (int)characters->GetScrollCenterX();
	int charaY = (int)characters->GetScrollCenterY();

	// 現在描画されているスクリーンの中心座標
	screenX = (charaX / ROOM_SIZE_X) * WIN_WIDTH + WIN_WIDTH / 2;
	screenY = (charaY / ROOM_SIZE_Y) * WIN_HEIGHT + WIN_HEIGHT / 2;
}

// スクロール座標の初期化処理
void SceneGame::InitScrollPos()
{
	// スクリーン座標の初期化処理
	InitScreenPos();

	// スクロール量
	scrollX = screenX - WIN_WIDTH / 2;
	scrollY = screenY - WIN_HEIGHT / 2;
}

// レターボックスの初期化処理
void SceneGame::InitLetterBox()
{
	// 左側縦のレターボックス
	letterBox[0].x1 = 0;
	letterBox[0].x2 = letterBox[0].x1 + DISPLACE_X;
	letterBox[0].y1 = 0;
	letterBox[0].y2 = WIN_HEIGHT;

	// 右側縦のレターボックス
	letterBox[1].x1 = WIN_WIDTH - DISPLACE_X;
	letterBox[1].x2 = letterBox[1].x1 + DISPLACE_X;
	letterBox[1].y1 = 0;
	letterBox[1].y2 = WIN_HEIGHT;

	// 上側横のレターボックス
	letterBox[2].x1 = 0;
	letterBox[2].x2 = WIN_WIDTH;
	letterBox[2].y1 = 0;
	letterBox[2].y2 = letterBox[2].y1 + DISPLACE_Y;

	// 下側横のレターボックス
	letterBox[3].x1 = 0;
	letterBox[3].x2 = WIN_WIDTH;
	letterBox[3].y1 = WIN_HEIGHT - DISPLACE_Y;
	letterBox[3].y2 = letterBox[3].y1 + DISPLACE_Y;

	// 色を設定
	for ( int i = 0; i < 4; i++ )
	{
		letterBox[i].h = 198.0f;
		letterBox[i].s = 84.0f;
		//letterBox[i].v = 117.0f;
		letterBox[i].v = 0.0f;
		// hsvからrgbに変換
		Utility::ConvertHSVtoRGB(&letterBox[i].r, &letterBox[i].g, &letterBox[i].b,
								 letterBox[i].h, letterBox[i].s, letterBox[i].v);
	}
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

	// UI
	ui->Initialize();

	// スクロール座標の初期化処理
	InitScrollPos();

	// オブジェクトをスクリーンの中心にずらす
	Utility::DisplaceObjScrnCntr(screenX, screenY,
								 &displaceX, &displaceY);

	// レターボックスの初期化処理
	InitLetterBox();

	isScroll = false;
	isDrawUIMM = false;

	r = g = b = 255.0f;
	h = s = v = 255.0f;

	isSceneChange = false;
}

// プレイヤーが左進行:-1,右進行:1を返す
int SceneGame::PlayerMoveLR()
{
	float moveX = characters->GetPlayerMoveX();
	if ( moveX > 0.0f )
	{
		return 1;
	}
	else if ( moveX < 0.0f )
	{
		return -1;
	}

	return 0;
}

// プレイヤーが上進行:-1,下進行:1を返す
int SceneGame::PlayerMoveUD()
{
	float moveY = characters->GetPlayerMoveY();
	if ( moveY > 0.0f )
	{
		return 1;
	}
	else if ( moveY < 0.0f )
	{
		return -1;
	}

	return 0;
}

// スクリーン座標を求める
void SceneGame::CalcScreenPos()
{
	screenX = scrollX + WIN_WIDTH / 2;
	screenY = scrollY + WIN_HEIGHT / 2;
}

// エフェクト管理
void SceneGame::MyEffectManager()
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

	// クリア時のエフェクト
	if ( characters->GetPlayerIsGoal() )
	{
		effects->Clear(characters->GetPlayerX(),
					   characters->GetPlayerY());
	}

	// エフェクト
	effects->Update();
}

// UI管理
void SceneGame::MyUIManager()
{
	// 更新処理
	ui->Update(characters->GetPlayerHp(),
			   characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(),
			   characters->GetPlayerMaxBattery(), isDrawUIMM);

	// 操作一覧表示中でない
	if ( !isDrawUIMM )
	{
		h = 0.0f;
		s = 0.0f;
		v = 255.0f;
	}
	// 操作一覧表示中
	else
	{
		h = 0.0f;
		s = 0.0f;
		v = 64.0f;
	}

	//  READYの場合は処理を行わない
	if ( ui->GetIsReady() )
	{
		return;
	}

	// ヘルプ(操作一覧を表示)
	if ( !isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE再生
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = true;
		return;
	}

	// ヘルプを閉じる
	if ( isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE再生
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = false;
		return;
	}
}

// シーン遷移
void SceneGame::SceneChange(bool isSCPossible)
{
	// シーン遷移が可能
	if ( !isSCPossible )
	{
		return;
	}

	// プレイヤーが死亡→初期化処理
	if ( !characters->GetPlayerIsAlive() )
	{
		// BGM停止
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);
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
		// BGM停止
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);

		// すべてのSE停止
		if ( !isSceneChange )
		{
			Sound_SE::GetInstance()->StopAllSE();
		}

		// SE(ジングル)再生
		Sound_SE::GetInstance()->PlaySE(e_STAGE_CLEAR_SE, true);
		nextScene = e_ENDING;
		isSceneChange = true;
		return;
	}
}

// レターボックスの描画処理
void SceneGame::DrawLetterBox()
{
	for ( int i = 0; i < 4; i++ )
	{
		int color = GetColor((int)letterBox[i].r,
							 (int)letterBox[i].g,
							 (int)letterBox[i].b);
		DrawBox(letterBox[i].x1, letterBox[i].y1,
				letterBox[i].x2, letterBox[i].y2,
				color, true);
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
void SceneGame::Update(bool isSCPossible)
{
	// BGM再生
	if ( !isSceneChange )
	{
		Sound_BGM::GetInstance()->PlayBGM(e_GAME_BGM);
	}

	// 操作一覧表示中は更新処理を行わない
	if ( !isDrawUIMM )
	{
		// SE再生
		if ( isScroll )
		{
			Sound_SE::GetInstance()->PlaySE(e_SCROLL_SE, true);
		}

		// スクロール
		Utility::Scroll((int)characters->GetScrollCenterX() +
						(int)displaceX + (DISPLACE_X * PlayerMoveLR()),
						(int)characters->GetScrollCenterY() +
						(int)displaceY + (DISPLACE_Y * PlayerMoveUD()),
						&scrollX, &scrollY, (int)displaceX, (int)displaceY, &isScroll);

		// エフェクト
		MyEffectManager();

		// スクロール中またはREADYの場合は更新処理を行わない
		if ( !isScroll && !ui->GetIsReady() )
		{
			// キャラクター
			characters->Update(screenX, screenY);
		}
	}

	// スクリーン座標を求める
	CalcScreenPos();

	// オブジェクトをスクリーンの中心にずらす
	Utility::DisplaceObjScrnCntr(screenX, screenY,
								 &displaceX, &displaceY);

	// キャラクターのdisplaceX,displaceYを設定
	characters->SetDisplaceX((int)displaceX);
	characters->SetDisplaceY((int)displaceY);

	// UI
	MyUIManager();

	// HSVからRGBへ変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);

	// シーン遷移
	SceneChange(isSCPossible);

	// ゲーム終了
	GameEnd();
}

// 描画処理
void SceneGame::Draw()
{
	SetDrawBright((int)r, (int)g, (int)b);
	// 背景
	Background back;
	back.Draw(effects->GetShakeX(), effects->GetShakeY(), 1);

	// ステージ
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(),
				scrollX, scrollY,
				screenX, screenY,
				(int)displaceX, (int)displaceY);

	// キャラクター
	characters->Draw(effects->GetShakeX(),
					 effects->GetShakeY(),
					 scrollX, scrollY);

	// エフェクト
	effects->Draw(scrollX, scrollY,
				  (int)displaceX, (int)displaceY);
	SetDrawBright(255, 255, 255);

	// レターボックス
	DrawLetterBox();

	// UI
	ui->Draw(characters->GetPlayerHp(),
			 characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(),
			 characters->GetPlayerMaxBattery(), isDrawUIMM);

	// 枠
	Frame frame;
	frame.Draw();
}