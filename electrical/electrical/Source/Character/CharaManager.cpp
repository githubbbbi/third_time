#include "DxLib.h"
#include "Chara_Manager.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyBombGH = LoadGraph("Resource/Graphic/Character/enemy_bomb.png");
	enemyGunGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	float startX = WIN_WIDTH / 2.0f;
	float startY = WIN_HEIGHT / 2.0f;

	// プレイヤー生成
	player = new Chara_Player(startX, startY, 32, 
							  PLAYER_WIDTH, PLAYER_HEIGHT,
							  NORMAL_SPEED, 100, 1, playerGH);
}

Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	{
		delete enemyBomb[i];
		enemyBomb.erase(enemyBomb.begin() + i);
	}

	for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	{
		delete enemyGun[i];
		enemyGun.erase(enemyGun.begin() + i);
	}
}

// 初期化処理
void Chara_Manager::Initialize()
{

}

// エネミー管理
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// テスト用
	{
		// 爆弾エネミー
		if ( CheckHitKey(KEY_INPUT_B) && enemyBomb.size() < 1 )
		{
			enemyBomb.push_back(new Chara_EnemyBomb(32.0f, 32.0f, 32,
													ENEMY_BOMB_WIDTH, ENEMY_BOMB_HEIGHT,
													NORMAL_SPEED, 2, 10, enemyBombGH));
		}

		// 銃エネミー
		if ( CheckHitKey(KEY_INPUT_A) && enemyGun.size() < 1 )
		{
			enemyGun.push_back(new Chara_EnemyGun(32.0f, 32.0f, 32,
												  ENEMY_GUN_WIDTH, ENEMY_GUN_HEIGHT,
												  GetRand(3) + 2.0f, 2, 2, enemyGunGH));
		}
	}

	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		enemyBomb[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive(),
							 &*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemyBomb.size() - 1; i >= 0; i-- )
	{
		// 死亡後画面外に出た場合、エネミー削除
		if ( !enemyBomb[i]->GetIsAlive() )
		{
			delete enemyBomb[i];
			enemyBomb.erase(enemyBomb.begin() + i);
		}
	}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->Update(player->GetPosX(), player->GetPosY(), player->GetIsAlive(),
							&*shakeAddX, &*shakeAddY);
	}

	for ( int i = enemyGun.size() - 1; i >= 0; i-- )
	{
		// 死亡後画面外に出た場合、エネミー削除
		if ( !enemyGun[i]->GetIsAlive() )
		{
			delete enemyGun[i];
			enemyGun.erase(enemyGun.begin() + i);
		}
	}
}

// キャラクタ同士の当たり判定
void Chara_Manager::CharaCollision()
{
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		// 敵とプレイヤーの判定
		// 敵と当たり、敵がダッシュ状態だったら、プレイヤーにダメージが入り敵が消える
		if ( enemyBomb[i]->GetIsAlive() && player->GetIsAlive()
			&& Utility::IsCircleCollision(
				enemyBomb[i]->GetPosX(),
				enemyBomb[i]->GetPosY(),
				enemyBomb[i]->GetRadius() - 8,
				player->GetPosX(),
				player->GetPosY(),
				player->GetRadius() - 8
			) )
			if ( enemyBomb[i]->GetSpeed() == DASH_SPEED )
			{
				enemyBomb[i]->ReceiveDamage(player->GetAttackPower() * 2);
				player->ReceiveDamage(enemyBomb[i]->GetAttackPower());
			}

		//// 敵と敵の当たり判定
		//for ( unsigned int j = 0; j < enemys.size(); j++ )
		//{
		//	// 自分と自分で判定しないように
		//	if ( j != i )
		//	{
		//		if ( enemys[i]->GetIsAlive() && enemys[j]->GetIsAlive()
		//			&& Utility::IsCircleCollision(
		//				enemys[i]->GetPosX(),
		//				enemys[i]->GetPosY(),
		//				enemys[i]->GetRadius() - 8,
		//				enemys[j]->GetPosX(),
		//				enemys[j]->GetPosY(),
		//				enemys[j]->GetRadius() - 8) )
		//		{
		//			enemys[j]->EnemiesCollision();
		//			enemys[j]->CharaJump();
		//		}
		//	}
		//}
	}
}

// 攻撃処理管理
void Chara_Manager::WeaponManager()
{
	// プレイヤー攻撃
	player->WeaponManager(electricGunGH);

	// 銃エネミー攻撃
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->WeaponManager(electricGunGH);
	}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	// 爆弾エネミー
	for ( unsigned int i = 0; i < enemyBomb.size(); i++ )
	{
		if ( !enemyBomb[i]->GetIsAlive() || !player->GetIsAlive() )
		{
			break;
		}

		// エネミーとプレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( enemyBomb[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemyBomb[i]->GetPosX(),
										   enemyBomb[i]->GetPosY(),
										   enemyBomb[i]->GetRadius() - 8,
										   player->GetGunPosX(j),
										   player->GetGunPosY(j),
										   player->GetGunRadius(j) - 4) )
			{
				enemyBomb[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
			}
		}
	}

	// 銃エネミー
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		if ( !enemyGun[i]->GetIsAlive() || !player->GetIsAlive() )
		{
			break;
		}

		// エネミーとプレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyGun[i]->GetPosX(),
											enemyGun[i]->GetPosY(),
											enemyGun[i]->GetRadius() - 8,
											player->GetGunPosX(j),
											player->GetGunPosY(j),
											player->GetGunRadius(j) - 4) )
			{
				enemyGun[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
			}
		}

		// エネミーの攻撃とプレイヤーの当たり判定
		for ( unsigned int j = 0; j < enemyGun[i]->GetGunSize(); j++ )
		{
			if ( Utility::IsCircleCollision(enemyGun[i]->GetGunPosX(j),
											enemyGun[i]->GetGunPosY(j),
											enemyGun[i]->GetGunRadius(j) - 8,
											player->GetPosX(),
											player->GetPosY(),
											player->GetRadius() - 4) )
			{
				enemyGun[i]->HitAttack(j);
				player->ReceiveDamage(enemyGun[i]->GetAttackPower());
			}
		}
	}
}

// 更新処理
void Chara_Manager::Update(float *shakeAddX, float *shakeAddY)
{
	// プレイヤー
	player->Update();

	//キャラの当たり判定
	CharaCollision();

	// 攻撃処理
	WeaponManager();

	// エネミー
	EnemyManager(&*shakeAddX, &*shakeAddY);

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
	for ( unsigned int i = 0; i < enemyGun.size(); i++ )
	{
		enemyGun[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}

	// デバッグ用
	DrawFormatString(50, 100, GetColor(255, 255, 255), "Bキーでエネミー生成 爆弾エネミーの数:%d", enemyBomb.size());
	DrawFormatString(50, 120, GetColor(255, 255, 255), "Aキーでエネミー生成 銃エネミーの数:%d", enemyGun.size());
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