#include "DxLib.h"
#include "Chara_Manager.h"
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

	for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	{
		delete enemyBomb[i];
		enemyBomb.erase(enemyBomb.begin() + i);
	}

	for ( int i = enemyElectric.size() - 1; i >= 0; i-- )
	{
		delete enemyElectric[i];
		enemyElectric.erase(enemyElectric.begin() + i);
	}
}

// 初期化処理
void Chara_Manager::Initialize()
{

}

// エネミー管理
void Chara_Manager::EnemyManager()
{
	// テスト用
	{
		float startX = 0.0f + CHIP_SIZE * 2.0f;
		float startY = 0.0f;

		static int timer = 0;
		timer++;
		// 爆弾エネミー
		if ( CheckHitKey(KEY_INPUT_B) && timer % 30 == 0 )
		{
			enemyBomb.push_back(new Chara_EnemyBomb(startX, startY, 32,
													E_BOMB_WIDTH, E_BOMB_HEIGHT,
													E_BOMB_NORMAL_SPEED, 2, 10));
		}

		// 銃エネミー
		if ( CheckHitKey(KEY_INPUT_A) && timer % 30 == 0 )
		{
			enemyElectric.push_back(new Chara_EnemyElectric(startX, startY, 32,
															E_GUN_WIDTH, E_GUN_HEIGHT,
															E_GUN_NORMAL_SPEED, 2, 2));
		}

		// 水弾エネミー
		if ( CheckHitKey(KEY_INPUT_C) && timer % 30 == 0 )
		{
			enemyWater.push_back(new Chara_EnemyWater(startX, startY, 32,
													  E_WATER_WIDTH, E_WATER_HEIGHT,
													  0.0f, 2, 2));
		}
	}

	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	//for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	//{
	//	// 死亡後画面外に出た場合、エネミー削除
	//	if ( !enemyBomb[i]->GetIsAlive() )
	//	{
	//		delete enemyBomb[i];
	//		enemyBomb.erase(enemyBomb.begin() + i);
	//	}
	//}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyElectric.size(); i++ )
	{
		enemyElectric[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive());
	}

	//for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	//{
	//	// 死亡後画面外に出た場合、エネミー削除
	//	if ( !enemyGun[i]->GetIsAlive() )
	//	{
	//		delete enemyGun[i];
	//		enemyGun.erase(enemyGun.begin() + i);
	//	}
	//}

	// 水弾エネミー
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		enemyWater[i]->Update(player->GetPosX(), player->GetPosY());
	}

	//for ( int i = enemyWater.size() - 1; i >= 0; i-- )
	//{
	//	// 死亡後画面外に出た場合、エネミー削除
	//	if ( !enemyWater[i]->GetIsAlive() )
	//	{
	//		delete enemyWater[i];
	//		enemyWater.erase(enemyWater.begin() + i);
	//	}
	//}
}

// キャラクタ同士の当たり判定
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		// プレイヤーと敵との判定
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		/*if ( Utility::IsRectCollision(enemyBomb[i]->GetPosX(),
									  enemyBomb[i]->GetPosY(),
									  enemyBomb[i]->GetWidth(),
									  enemyBomb[i]->GetHeight(),
									  player->GetPosX(),
									  player->GetPosY(),
									  player->GetWidth(),
									  player->GetHeight()) )
		{
			player->CharactersCollision();
		}*/
	}
}

// 武器処理管理
void Chara_Manager::WeaponManager()
{
	// プレイヤー攻撃
	player->WeaponManager();

	// 銃エネミー攻撃
	for ( unsigned int i = 0; i < enemyElectric.size(); i++ )
	{
		enemyElectric[i]->WeaponManager();
	}

	// 水弾エネミー攻撃
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		enemyWater[i]->WeaponManager(player->GetPosX(), player->GetPosY(),
									 player->GetIsAlive());
	}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	if ( !player->GetIsAlive() )
	{
		return;
	}

	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		// プレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
											enemyBomb[i]->GetPosY(),
											enemyBomb[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemyBomb[i]->ReceiveDamage(player->GetAttackPower(),
											player->GetIsGunLeftWard(j));
				player->HitAttack(j);
			}
		}

		// 爆弾エネミーがダッシュ状態だったら、プレイヤーにダメージが入り敵が消える
		if ( !player->GetIsInvicible() &&
			Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
									   enemyBomb[i]->GetPosY(),
									   enemyBomb[i]->GetRadius() - 8,
									   player->GetPosX(),
									   player->GetPosY(),
									   player->GetRadius() - 8) )
		{
			if ( fabsf(enemyBomb[i]->GetSpeed()) == E_BOMB_DASH_SPEED )
			{
				enemyBomb[i]->HitAttack();
				player->ReceiveDamage(enemyBomb[i]->GetAttackPower(),
									  enemyBomb[i]->GetIsLeftWard());
			}
		}
	}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyElectric.size(); i++ )
	{
		if ( !enemyElectric[i]->GetIsAlive() )
		{
			continue;
		}

		// プレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyElectric[i]->GetPosX(),
											enemyElectric[i]->GetPosY(),
											enemyElectric[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemyElectric[i]->ReceiveDamage(player->GetAttackPower(),
												player->GetIsGunLeftWard(j));
				player->HitAttack(j);
			}
		}

		// エネミーの攻撃とプレイヤーの当たり判定
		for ( unsigned int j = 0; j < enemyElectric[i]->GetGunSize(); j++ )
		{
			if ( !player->GetIsInvicible() &&
				Utility::IsCircleCollision(enemyElectric[i]->GetGunPosX(j),
										   enemyElectric[i]->GetGunPosY(j),
										   enemyElectric[i]->GetGunRadius(j) - 8,
										   player->GetPosX(),
										   player->GetPosY(),
										   player->GetRadius() - 4) )
			{
				enemyElectric[i]->HitAttack(j);
				player->ReceiveDamage(enemyElectric[i]->GetAttackPower(),
									  enemyElectric[i]->GetIsGunLeftWard(j));
			}
		}
	}

	// 水弾エネミー
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		if ( !enemyWater[i]->GetIsAlive() )
		{
			continue;
		}

		// プレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyWater[i]->GetPosX(),
											enemyWater[i]->GetPosY(),
											enemyWater[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemyWater[i]->ReceiveDamage(player->GetAttackPower(),
											 player->GetIsGunLeftWard(j));
				player->HitAttack(j);
			}
		}

		// エネミーの攻撃とプレイヤーの当たり判定
		for ( unsigned int j = 0; j < enemyWater[i]->GetGunSize(); j++ )
		{
			if ( !player->GetIsInvicible() &&
				Utility::IsCircleCollision(enemyWater[i]->GetGunPosX(j),
										   enemyWater[i]->GetGunPosY(j),
										   enemyWater[i]->GetGunRadius(j) - 8,
										   player->GetPosX(),
										   player->GetPosY(),
										   player->GetRadius() - 4) )
			{
				enemyWater[i]->HitAttack(j);
				player->ReceiveDamage(enemyWater[i]->GetAttackPower(),
									  enemyWater[i]->GetIsGunLeftWard(j));
			}
		}
	}
}

// 更新処理
void Chara_Manager::Update()
{
	// プレイヤー
	player->Update();

	//キャラの当たり判定
	CharaCollision();

	// 武器処理
	WeaponManager();

	// エネミー
	EnemyManager();

	// 攻撃の当たり判定
	AttackCollision();
}

// 描画処理
void Chara_Manager::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// プレイヤー
	player->Draw(shakeX, shakeY, scrollX, scrollY);

	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyElectric.size(); i++ )
	{
		enemyElectric[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// 水弾エネミー
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		enemyWater[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// デバッグ用
	DrawFormatString(50, 100, GetColor(255, 255, 255), "Bキーでエネミー生成 爆弾エネミーの数:%d", enemyBomb.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "Aキーでエネミー生成 銃エネミーの数:%d", enemyElectric.size());
	DrawFormatString(50, 140, GetColor(255, 255, 255), "Cキーでエネミー生成 水弾エネミーの数:%d", enemyWater.size());
	DrawFormatString(300, 200, GetColor(255, 255, 255), "プレイヤーのY座標%f", player->GetPosY());
	if ( enemyBomb.size() >= 1 )
	{
		DrawFormatString(300, 220, GetColor(255, 255, 255), "敵のX座標%f", enemyBomb[0]->GetPosX());
		DrawFormatString(300, 240, GetColor(255, 255, 255), "敵のY座標%f", enemyBomb[0]->GetPosY());
	}
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

// エネミーの死亡
bool Chara_Manager::GetIsEnemyDeath()
{
	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( enemyBomb[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemyBomb[i]->GetIsAlive() )
		{
			// 座標を取得
			explosionX = enemyBomb[i]->GetPosX();
			explosionY = enemyBomb[i]->GetPosY();

			// エネミーを消去
			delete enemyBomb[i];
			enemyBomb.erase(enemyBomb.begin() + i);

			return true;
		}
	}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyElectric.size(); i++ )
	{
		if ( enemyElectric[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemyElectric[i]->GetIsAlive() )
		{
			// 座標を取得
			explosionX = enemyElectric[i]->GetPosX();
			explosionY = enemyElectric[i]->GetPosY();

			// エネミーを消去
			delete enemyElectric[i];
			enemyElectric.erase(enemyElectric.begin() + i);

			return true;
		}
	}

	// 水弾エネミー
	for ( unsigned int i = 0; i < enemyWater.size(); i++ )
	{
		if ( enemyWater[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemyWater[i]->GetIsAlive() )
		{
			// 座標を取得
			explosionX = enemyWater[i]->GetPosX();
			explosionY = enemyWater[i]->GetPosY();

			// エネミーを消去
			delete enemyWater[i];
			enemyWater.erase(enemyWater.begin() + i);

			return true;
		}
	}

	return false;
}