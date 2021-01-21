#include "DxLib.h"
#include "Chara_Manager.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"

Chara_Manager::Chara_Manager()
{
	explosionX = 0.0f;
	explosionY = 0.0f;

	float startX = 0.0f + CHIP_SIZE * 2.0f;
	float startY = 0.0f;

	// プレイヤー生成
	player = new Chara_Player(startX, startY, 32,
							  P_WIDTH, P_HEIGHT,
							  P_NORMAL_SPEED, 100, 1);
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
	player->Initialize();

	// エネミーは全て消去しちゃう
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// エネミーの生成
void Chara_Manager::EnemySpawn(int screenX, int screenY)
{
	// テスト用
	float startX = 0.0f + CHIP_SIZE * 2.0f;
	float startY = 0.0f;
	static int timer = 0;
	timer++;

	// 爆弾エネミー
	if ( CheckHitKey(KEY_INPUT_B) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyBomb(startX, startY, 32,
											 EB_WIDTH, EB_HEIGHT,
											 EB_NORMAL_SPEED, 2, 10));
	}

	// 銃エネミー
	if ( CheckHitKey(KEY_INPUT_A) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyElectric(startX, startY, 32,
												 EE_WIDTH, EE_HEIGHT,
												 EE_NORMAL_SPEED, 2, 2));
	}

	// 水弾エネミー
	if ( CheckHitKey(KEY_INPUT_C) && timer % 30 == 0 )
	{
		enemys.push_back(new Chara_EnemyWater(startX, startY, 32,
											  EW_WIDTH, EW_HEIGHT,
											  0.0f, 2, 2));
	}
}

// エネミー管理
void Chara_Manager::EnemyManager(int screenX, int screenY)
{
	// エネミーの出現
	EnemySpawn(screenX, screenY);

	// 更新処理
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	// スクリーン外に出た場合消去
	/*for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}*/
}

// キャラクタ同士の当たり判定
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	//for ( unsigned int i = 0; i < enemys.size(); i++ )
	//{
	//	// プレイヤーと敵との判定
	//	if ( !enemys[i]->GetIsAlive() )
	//	{
	//		continue;
	//	}

	//	if ( Utility::IsRectCollision(enemys[i]->GetPosX(),
	//								  enemys[i]->GetPosY(),
	//								  enemys[i]->GetWidth(),
	//								  enemys[i]->GetHeight(),
	//								  player->GetPosX(),
	//								  player->GetPosY(),
	//								  player->GetWidth(),
	//								  player->GetHeight()) )
	//	{
	//		player->CharactersCollision();
	//	}
	//}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			continue;
		}

		// プレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemys[i]->GetPosX(),
											enemys[i]->GetPosY(),
											enemys[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower(),
										 player->GetIsGunLeftWard(j));
				player->HitAttack(j);
			}
		}

		if ( player->GetIsInvicible() )
		{
			return;
		}

		// エネミーの攻撃とプレイヤーの当たり判定
		if ( Utility::IsCircleCollision(enemys[i]->GetAttackPosX(),
									   enemys[i]->GetAttackPosY(),
									   enemys[i]->GetAttackRadius() - 8,
									   player->GetPosX(),
									   player->GetPosY(),
									   player->GetRadius() - 4) )
		{
			enemys[i]->HitAttack();
			player->ReceiveDamage(enemys[i]->GetAttackPower(),
								  enemys[i]->GetIsAttackLeftWard());
		}
		/*for ( unsigned int j = 0; j < enemys[i]->GetGunSize(); j++ )
		{
			if ( !player->GetIsInvicible() &&
				Utility::IsCircleCollision(enemys[i]->GetGunPosX(j),
										   enemys[i]->GetGunPosY(j),
										   enemys[i]->GetGunRadius(j) - 8,
										   player->GetPosX(),
										   player->GetPosY(),
										   player->GetRadius() - 4) )
			{
				enemys[i]->HitAttack(j);
				player->ReceiveDamage(enemys[i]->GetAttackPower(),
									  enemys[i]->GetIsGunLeftWard(j));
			}
		}*/
	}
}

// 更新処理
void Chara_Manager::Update(int screenX, int screenY)
{
	// プレイヤー
	player->Update();

	//キャラの当たり判定
	CharaCollision();

	// エネミー
	EnemyManager(screenX, screenY);

	// 攻撃の当たり判定
	AttackCollision();
}

// 描画処理
void Chara_Manager::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// プレイヤー
	player->Draw(shakeX, shakeY, scrollX, scrollY);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// デバッグ用
	DrawFormatString(50, 100, GetColor(255, 255, 255), "Bキーでエネミー生成 爆弾エネミーの数:%d", enemys.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "Aキーでエネミー生成 銃エネミーの数:%d", enemys.size());
	DrawFormatString(50, 140, GetColor(255, 255, 255), "Cキーでエネミー生成 水弾エネミーの数:%d", enemys.size());
	/*DrawFormatString(300, 200, GetColor(255, 255, 255), "プレイヤーのY座標%f", player->GetPosY());
	if ( enemyBomb.size() >= 1 )
	{
		DrawFormatString(300, 220, GetColor(255, 255, 255), "敵のX座標%f", enemyBomb[0]->GetPosX());
		DrawFormatString(300, 240, GetColor(255, 255, 255), "敵のY座標%f", enemyBomb[0]->GetPosY());
	}*/
}

// スクロールの中心X座標を取得
float Chara_Manager::GetScrollCenterX()
{
	return player->GetPosOldX();
}

// スクロールの中心Y座標を取得
float Chara_Manager::GetScrollCenterY()
{
	return player->GetPosOldY();
}

// エネミーの死亡X座標を取得
float Chara_Manager::GetExplosionPosX()
{
	return explosionX;
}

// エネミーの死亡Y座標を取得
float Chara_Manager::GetExplosionPosY()
{
	return explosionY;
}

// キャラクターの死亡
bool Chara_Manager::GetIsCharaDeath()
{
	// プレイヤー
	if ( !player->GetIsAlive() )
	{
		// 座標を取得
		explosionX = player->GetPosX();
		explosionY = player->GetPosY();

		return true;
	}

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemys[i]->GetIsAlive() )
		{
			// 座標を取得
			explosionX = enemys[i]->GetPosX();
			explosionY = enemys[i]->GetPosY();

			// エネミーを消去
			delete enemys[i];
			enemys.erase(enemys.begin() + i);

			return true;
		}
	}

	return false;
}