#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

#define ENEMY_MAX_NUM 1000

Chara_Manager::Chara_Manager()
{
	player = nullptr;
	enemyAbsorption = new Chara_EnemyAbsorption * [ENEMY_MAX_NUM];

	enemyAbsorptionNum = 0;

	playerGH = LoadGraph("Resource/Graphic/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/enemy_absorption.png");
}

Chara_Manager::~Chara_Manager()
{
	delete player;
	delete[] enemyAbsorption;
}

// 初期化処理
void Chara_Manager::Initialize()
{
	// プレイヤー生成
	player = new Chara_Player(WIN_WIDTH / 2, WIN_HEIGHT / 2,
							  32, 5, 50, playerGH);

	// エネミー生成
	enemyAbsorption[enemyAbsorptionNum] =
	{
		new Chara_EnemyAbsorption(32, WIN_HEIGHT / 2,
								   32, 5, 2, enemyAbsorptionGH)
	};

	enemyAbsorptionNum = 1;
}

// 更新処理
void Chara_Manager::Update()
{
	// プレイヤー
	player->Update();

	// エネミー
	// 吸収
	// テスト
	{
		// パッドのAボタンでエネミー生成
		if ( InputPad::IsPadInputTrigger(PAD_INPUT_A) &&
			enemyAbsorptionNum < ENEMY_MAX_NUM )
		{
			enemyAbsorption[enemyAbsorptionNum] =
			{
				new Chara_EnemyAbsorption(32, GetRand(WIN_HEIGHT - 64) + 32,
										  32, GetRand(3) + 2, 2,enemyAbsorptionGH)
			};

			enemyAbsorptionNum++;
		}
	}

	for ( int i = 0; i < enemyAbsorptionNum; i++ )
	{
		enemyAbsorption[i]->Update();
	}
}

// 描画処理
void Chara_Manager::Draw()
{
	// プレイヤー
	player->Draw();

	// エネミー
	// 吸収
	for ( int i = 0; i < enemyAbsorptionNum; i++ )
	{
		enemyAbsorption[i]->Draw();
	}
}