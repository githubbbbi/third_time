#include "DxLib.h"
#include "SceneTitle.h"
#include "../Input/InputManager.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"
#include "../Background/Background.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

SceneTitle::SceneTitle()
{
	ui = new UI_Title;
	GetGraphSize(Graphic::GetInstance()->GetTitle(), &width, &height);
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2 - height / 2;
}

SceneTitle::~SceneTitle()
{
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		delete lightnings[i];
		lightnings.erase(lightnings.begin() + i);
	}

	delete ui;
}

// 初期化処理
void SceneTitle::Initialize()
{
	isSceneChange = false;
}

// ライトニング更新処理
void SceneTitle::LightningUpdate()
{
	const int wallX1 = x - width / 2;
	const int wallY1 = y - height / 2;
	const int wallX2 = x + width / 2;
	const int wallY2 = y + height / 2;

	// 最大生成数50個
	if ( lightnings.size() <= 50 )
	{
		// 1フレーム3個
		for ( int i = 0; i < 3; i++ )
		{
			lightnings.push_back(new Effect_Lightning(wallX1, wallY1, wallX2, wallY2));
		}
	}

	// 更新
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Update();
	}

	// 消去
	for ( int i = lightnings.size() - 1; i >= 0; i-- )
	{
		if ( lightnings[i]->IsLengthOver() )
		{
			delete lightnings[i];
			lightnings.erase(lightnings.begin() + i);
		}
	}
}

// ライトニング描画処理
void SceneTitle::LightningDraw()
{
	for ( unsigned int i = 0; i < lightnings.size(); i++ )
	{
		lightnings[i]->Draw();
	}
}

// シーン遷移判定
bool SceneTitle::IsSceneChange()
{
	return InputManager::IsInputRelease(e_START);
}

// シーン遷移
void SceneTitle::SceneChange()
{
	// メインゲームへ遷移
	if ( IsSceneChange() )
	{
		nextScene = e_GAME;

		// BGM停止
		Sound_BGM::GetInstance()->StopBGM(e_TITLE_BGM);

		// SE再生
		if ( !isSceneChange )
		{
			Sound_SE::GetInstance()->PlaySE(e_GAME_START_SE, true);
		}

		isSceneChange = true;
	}
}

// ゲーム終了
void SceneTitle::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneTitle::Update()
{
	// BGM再生
	if ( !isSceneChange )
	{
		Sound_BGM::GetInstance()->PlayBGM(e_TITLE_BGM);
	}

	LightningUpdate();

	// タイトルUI シーン遷移時に点滅、そうでなければ明滅
	ui->Update(!isSceneChange, isSceneChange);
	SceneChange();
	GameEnd();
}

// 描画処理
void SceneTitle::Draw()
{
	// 背景
	Background back;
	back.Draw(0.0f, 0.0f);

	LightningDraw();
	DrawRotaGraph(x, y, 1.0, 0.0,
				  Graphic::GetInstance()->GetTitle(), true);

	ui->Draw();
}