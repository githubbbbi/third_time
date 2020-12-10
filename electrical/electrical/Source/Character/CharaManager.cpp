#include "../Utility/Utility.h"
#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	player = nullptr;

	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");
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

// 攻撃処理の管理
void Chara_Manager::WeaponManager()
{
	// 生成
	if ( player->IsAttack() )
	{
		electricGun.push_back(new ElectricGun(player->GetPosX(),
											  player->GetPosY(),
											  16, 15, electricGunGH));
	}
	
	// 電気銃
	for ( int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Update();
	}

	// 電気銃削除
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		if ( !electricGun[i]->GetIsAlive() )
		{
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}
	}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	for ( int i = 0; i < enemys.size(); i++ )
	{
		// エネミーとプレイヤーの攻撃との当たり判定
		for ( int i = 0; i < electricGun.size(); i++ )
		{
			// ここから

			if (Utility::IsCircleCollision(electricGun[i]->GetPosX(), electricGun[i]->GetPosY(), electricGun[i]->GetRadius(),
										   enemys[i]->GetPosX(), enemys[i]->GetPosY(), enemys[i]->GetRadius()))
			{
				electricGun[i]->BulletHit();
				enemys[i]->ReceiveDamage(player->GetAttackPower());
			}

			//enemys[i]->GetPosX()
			//electricGun[i]->GetPosX()って感じで座標は取得できる！この書き方でそれぞれのX、Y座標と半径を取得してください

			// プレイヤーの攻撃とヒットした時、↓の関数が呼ばれる
			// electricGun[i]->BulletHit();
			// enemys[i]->ReceiveDamage(player->GetAttackPower());

			// 必要な関数はこれだけ、引数は使う必要はないと思う

			// ここまで
		}
	}
}

// 更新処理
void Chara_Manager::Update()
{
	// プレイヤー
	player->Update();

	// 攻撃処理
	WeaponManager();

	// エネミー
	EnemyManager();

	// 攻撃の当たり判定
	AttackCollision();
}

// 描画処理
void Chara_Manager::Draw()
{
	// 電気銃
	for ( int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw();
	}

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