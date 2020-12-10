#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	player = nullptr;

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// 初期化処理
void Chara_Manager::Initialize()
{
	// プレイヤー生成
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, 5.0f, 50, 1, playerGH);
}

// エネミー管理
void Chara_Manager::EnemyManager()
{
	// 吸収
	// テスト
	{
		// パッドのAボタンでエネミー生成
		if ( InputPad::IsPadInputNow(PAD_INPUT_B) )
		{
			// 吸収エネミー
			enemys.push_back(new Chara_EnemyAbsorption(32.0f, 32.0f, 32,
													   GetRand(3) + 2.0f, 2, 20, enemyAbsorptionGH));
		}
	}

	for ( int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update();
	}

	// エネミー削除
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	for ( int i = 0; i < enemys.size(); i++ )
	{
		// エネミーとプレイヤーの攻撃との当たり判定
		// ここから


		// ここまで

		// プレイヤーの攻撃とヒットした時、↓の関数が呼ばれる　まんま使って大丈夫なはず
		// enemys[i]->ReceiveDamage(player->GetAttackPower());
	}
}

// 更新処理
void Chara_Manager::Update()
{
	// プレイヤー
	player->Update();

	// エネミー
	EnemyManager();

	// 攻撃の当たり判定
	AttackCollision();
}

// 描画処理
void Chara_Manager::Draw()
{
	// プレイヤー
	player->Draw();

	// エネミー
	for ( int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw();
	}

	// デバッグ用
	DrawFormatString(0, 20, GetColor(255, 255, 255), "XキーまたはBボタンでエネミー生成 エネミーの数:%d", enemys.size());
	DrawFormatString(0, 40, GetColor(255, 255, 255), "SPACEキーまたはXボタンで攻撃(マイナス方向にしかいきません)");
}