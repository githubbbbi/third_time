#include "../Utility/Utility.h"
#include "DxLib.h"
#include "../Define/Define.h"
#include "Chara_Manager.h"
#include "../Character/Chara_EnemyBomb.h"
#include "../Character/Chara_EnemyGun.h"

Chara_Manager::Chara_Manager()
{
	playerGH = LoadGraph("Resource/Graphic/Character/player.png");
	enemyBombGH = LoadGraph("Resource/Graphic/Character/enemy_bomb.png");
	enemyGunGH = LoadGraph("Resource/Graphic/Character/enemy_gun.png");
	electricGunGH = LoadGraph("Resource/Graphic/Weapon/electricGun.png");

	// プレイヤー生成
	player = new Chara_Player(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f,
							  32, NORMAL_SPEED, 100, 1, playerGH);
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

}

// エネミー管理
void Chara_Manager::EnemyManager(float *shakeAddX, float *shakeAddY)
{
	// テスト用
	{
		// 爆弾エネミー
		if ( CheckHitKey(KEY_INPUT_B) )
		{
			enemys.push_back(new Chara_EnemyBomb(32.0f, 32.0f, 32,
												NORMAL_SPEED, 2, 20, enemyBombGH));
		}

		// 銃エネミー
		if ( CheckHitKey(KEY_INPUT_A) )
		{
			enemys.push_back(new Chara_EnemyGun(32.0f, 32.0f, 32,
												 GetRand(3) + 2.0f, 2, 20, enemyGunGH));
		}
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Update(player->GetPosX(), player->GetPosY(),
						  &*shakeAddX, &*shakeAddY);
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
		// 敵とプレイヤーの判定
		// 同じ方向を向いていてプレイヤーが敵の後ろを追いかける場合、敵は進む
		//if ( enemys[i]->GetIsAlive() && player->GetIsAlive()
		//	&& Utility::IsCircleCollision(
		//		enemys[i]->GetPosX(),
		//		enemys[i]->GetPosY(),
		//		enemys[i]->GetRadius() - 8,
		//		player->GetPosX(),
		//		player->GetPosY(),
		//		player->GetRadius() - 8
		//	) )
		//	if ( !enemys[i]->GetIsLeftWard() && !player->GetIsLeftWard()
		//		&& enemys[i]->GetPosX() > player->GetPosX()
		//		|| enemys[i]->GetIsLeftWard() && player->GetIsLeftWard()
		//		&& enemys[i]->GetPosX() < player->GetPosX() )
		//	{
		//		player->CharactersCollision();
		//		player->CharaJump();
		//	}
		//	else
		//	{
		//		player->CharaJump();
		//		player->CharactersCollision();
		//		enemys[i]->CharactersCollision();
		//	}

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

	// エネミー攻撃
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->WeaponManager(electricGunGH);
	}
}

// 攻撃の当たり判定
void Chara_Manager::AttackCollision()
{
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		// エネミーとプレイヤーの攻撃との当たり判定
		for ( unsigned int j = 0; j < player->GetGunSize(); j++ )
		{
			if ( enemys[i]->GetIsAlive() &&
				Utility::IsCircleCollision(enemys[i]->GetPosX(),
										   enemys[i]->GetPosY(),
										   enemys[i]->GetRadius() - 8,
										   player->GetGunPosX(j),
										   player->GetGunPosY(j),
										   player->GetGunRadius(j) - 4) )
			{
				enemys[i]->ReceiveDamage(player->GetAttackPower());
				player->HitAttack(j);
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
void Chara_Manager::Draw(float shakeX, float shakeY)
{
	// プレイヤー
	player->Draw(shakeX, shakeY);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY);
	}

	// デバッグ用
	DrawFormatString(0, 100, GetColor(255, 255, 255), "Bキーでエネミー生成 エネミーの数:%d", enemys.size());
}