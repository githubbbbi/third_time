#include "../Utility/Utility.h"
#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyAbsorptionGH = LoadGraph("Resource/Graphic/Character/enemy_absorption.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	// プレイヤー生成
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, NORMAL_SPEED, 100, 1, playerGH);
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// 初期化処理
void Chara_Manager::Initialize()
{
	
}

// エネミー管理
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// 吸収
	// テスト Bキー、パッドのBボタンでエネミー生成
	if ( InputKey::IsKeyInputNow(KEY_INPUT_B) ||
		InputPad::IsPadInputNow(PAD_INPUT_B) )
	{
		// 吸収エネミー
		enemys.push_back(new Chara_EnemyAbsorption(32.0f, 32.0f, 32,
												   GetRand(3) + 2.0f, 2, 20, enemyAbsorptionGH));
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(&*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		// 死亡後画面外に出た場合、エネミー削除
		if ( !enemys[i]->GetIsAlive() )
		{
 			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// キャラクタ同士の当たり判定
void Chara_Manager::CharaCollision()
{
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// ここに記述

		// プレイヤーと敵が接触した場合↓の関数を呼ぶ
		//player->CharaCollision();
		//enemys[i]->CharaCollision();
	}
}

// 攻撃処理の管理
void Chara_Manager::WeaponManager()
{
	// 生成
	if ( player->IsAttack() && player->GetIsAlive() )
	{
		electricGun.push_back(new ElectricGun(player->GetPosX(),
											  player->GetPosY(),
											  16, 25,
											  player->GetIsLeftWard(),
											  electricGunGH));
	}

	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
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
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// エネミーとプレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < electricGun.size(); j++ )
		{
			if ( enemys[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemys[i]->GetPosX(),
										   enemys[i]->GetPosY(),
										   enemys[i]->GetRadius() - 8,
										   electricGun[j]->GetPosX(),
										   electricGun[j]->GetPosY(),
										   electricGun[j]->GetRadius() - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower());
				electricGun[j]->BulletHit();
			}
		}
	}
}

// 更新処理
void Chara_Manager::Update(float *shakeAddX, float *shakeAddY)
{
	// プレイヤー
	player->Update();

	// 攻撃処理
	WeaponManager();

	// エネミー
	EnemyManager(&*shakeAddX, &*shakeAddY);

	// 攻撃の当たり判定
	AttackCollision();
}

// 描画処理
void Chara_Manager::Draw(float shakeX, float shakeY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw();
	}

	// プレイヤー
	player->Draw(shakeX, shakeY);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY);
	}

	// デバッグ用
	DrawFormatString(0, 20, GetColor(255, 255, 255), "Bボタンでエネミー生成 エネミーの数:%d", enemys.size());
	DrawFormatString(0, 40, GetColor(255, 255, 255), "SPACEキーまたはXボタンで攻撃");
}