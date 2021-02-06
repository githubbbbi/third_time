#include "DxLib.h"
#include "Chara_Manager.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Resource/CSV.h"

// コンストラクタ
Chara_Manager::Chara_Manager()
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			spawnData[y][x] = -1;
			isEnemySpawn[y][x] = false;
		}
	}

	displaceX = 0;
	displaceY = 0;

	explosionX = 0.0f;
	explosionY = 0.0f;

	isPassCheckPoint = false;

	// プレイヤー生成
	player = new Chara_Player(0.0f, 0.0f, 32,
							  P_WIDTH, P_HEIGHT,
							  P_NORMAL_SPEED, 100, 1);
}

// デストラクタ
Chara_Manager::~Chara_Manager()
{
	delete player;

	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}
}

// ファイル読み込み
bool Chara_Manager::LoadFile()
{
	// 読み込むファイル名を格納する
	char fileName[512];
	sprintf_s(fileName, sizeof(fileName),
			  "Resource/Data/Spawn_Position/spawn_stage%d.csv", 1);

	// ファイルが読み込めない場合、false
	int *p = (int *)spawnData;
	if ( !CSV::LoadFile(fileName,
						MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// プレイヤーのスポーン
void Chara_Manager::PlayerSpawn()
{
	auto SpawnPos = [](int x)->float
	{
		return (float)(x * CHARA_SIZE + CHARA_SIZE / 2);
	};

	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			// チェックポイント
			if ( isPassCheckPoint )
			{
				if ( spawnData[y][x] == e_CharaPlayer_ChecKPoint )
				{
					player->Spawn(SpawnPos(x), SpawnPos(y));
					return;
				}

				continue;
			}

			// 通常スポーン
			if ( spawnData[y][x] == e_CharaPlayer )
			{
				player->Spawn(SpawnPos(x), SpawnPos(y));
				return;
			}
		}
	}
}

// 初期化処理
bool Chara_Manager::Initialize()
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			spawnData[y][x] = -1;
			isEnemySpawn[y][x] = false;
		}
	}

	// ファイル読み込み
	if ( !LoadFile() )
	{
		return false;
	}

	// プレイヤーのスポーン
	PlayerSpawn();

	// プレイヤーの変数初期化
	player->Initialize();

	// エネミーは全て消去しちゃう
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		delete enemys[i];
		enemys.erase(enemys.begin() + i);
	}

	return true;
}

// エネミーの生成
void Chara_Manager::EnemyGenerate(int screenX, int screenY)
{
	// スクリーンに映っている部分だけ
	int mapChipLeft = (screenX - WIN_WIDTH / 2 -
					   displaceX + DISPLACE_X) / CHIP_SIZE;
	int mapChipRight = (screenX + WIN_WIDTH / 2 -
						displaceX - DISPLACE_X) / CHIP_SIZE - 1;
	int mapChipTop = (screenY - WIN_HEIGHT / 2 -
					  displaceY + DISPLACE_Y) / CHIP_SIZE;
	int mapChipBottom = (screenY + WIN_HEIGHT / 2 -
						 displaceY - DISPLACE_Y) / CHIP_SIZE - 1;

	if ( mapChipLeft < 0 )
	{
		mapChipLeft = 0;
	}

	if ( mapChipRight > MAP_COUNT_X )
	{
		mapChipRight = MAP_COUNT_X;
	}

	if ( mapChipTop < 0 )
	{
		mapChipTop = 0;
	}

	if ( mapChipBottom > MAP_COUNT_Y )
	{
		mapChipBottom = MAP_COUNT_Y;
	}

	for ( int y = mapChipTop; y < mapChipBottom; y++ )
	{
		for ( int x = mapChipLeft; x < mapChipRight; x++ )
		{
			// 湧いてる場合はスキップ
			if ( isEnemySpawn[y][x] )
			{
				continue;
			}

			// スポーン位置
			float spawnX = (float)(x * CHIP_SIZE + CHARA_SIZE / 2);
			float spawnY = (float)(y * CHIP_SIZE + CHARA_SIZE / 2);

			// スピード(プレイヤーへ向かう)
			float playerX = player->GetPosX();
			auto Speed = [playerX, x]()->float
			{
				if ( playerX < x * CHIP_SIZE )
				{
					return -1.0f;
				}

				return 1.0f;
			};
			float speed = Speed();

			switch ( spawnData[y][x] )
			{
				case e_CharaEnemyBomb:
					// 爆弾エネミー
					speed *= EB_NORMAL_SPEED;
					enemys.push_back(new Chara_EnemyBomb(spawnX, spawnY,
														 32, EB_WIDTH, EB_HEIGHT,
														 speed, 10, 10, x, y));

					isEnemySpawn[y][x] = true;
					break;

				case e_CharaEnemyElectric:
					// 銃エネミー
					speed *= EE_NORMAL_SPEED;
					enemys.push_back(new Chara_EnemyElectric(spawnX, spawnY,
															 32, EE_WIDTH, EE_HEIGHT,
															 speed, 5, 5, x, y));
					isEnemySpawn[y][x] = true;
					break;

				case e_CharaEnemyWater:
					// 水弾エネミー
					enemys.push_back(new Chara_EnemyWater(spawnX, spawnY,
														  32, EW_WIDTH, EW_HEIGHT,
														  0.0f, 2, 2, x, y));
					isEnemySpawn[y][x] = true;
					break;

				default:
					break;
			}
		}
	}
}

// エネミー管理
void Chara_Manager::EnemyManager(int screenX, int screenY)
{
	// エネミーの生成
	EnemyGenerate(screenX, screenY);

	// 更新処理
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->SetDisplaceX(displaceX);
		enemys[i]->SetDisplaceY(displaceY);
		enemys[i]->Update(player->GetPosX(), player->GetPosY(),
						  screenX, screenY, player->GetIsAlive());
	}

	int mapChipLeft = (screenX - WIN_WIDTH / 2 -
					   displaceX + DISPLACE_X) / CHIP_SIZE;
	int mapChipRight = (screenX + WIN_WIDTH / 2 -
						displaceX - DISPLACE_X) / CHIP_SIZE - 1;
	int mapChipTop = (screenY - WIN_HEIGHT / 2 -
					  displaceY + DISPLACE_Y) / CHIP_SIZE;
	int mapChipBottom = (screenY + WIN_HEIGHT / 2 -
						 displaceY - DISPLACE_Y) / CHIP_SIZE - 1;

	if ( mapChipLeft < 0 )
	{
		mapChipLeft = 0;
	}

	if ( mapChipRight > MAP_COUNT_X )
	{
		mapChipRight = MAP_COUNT_X;
	}

	if ( mapChipTop < 0 )
	{
		mapChipTop = 0;
	}

	if ( mapChipBottom > MAP_COUNT_Y )
	{
		mapChipBottom = MAP_COUNT_Y;
	}

	// 消去
	for ( int i = enemys.size() - 1; i >= 0; i-- )
	{
		// スポーン位置がスクリーン外の場合
		if ( (enemys[i]->GetMapChipX() < mapChipLeft ||
			  enemys[i]->GetMapChipX() > mapChipRight) ||
			(enemys[i]->GetMapChipY() < mapChipTop ||
			 enemys[i]->GetMapChipY() > mapChipBottom) )
		{
			isEnemySpawn[enemys[i]->GetMapChipY()][enemys[i]->GetMapChipX()] = false;

			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}
}

// キャラクタ同士の当たり判定
void Chara_Manager::CharaCollision()
{
	if ( !player->GetIsAlive() || player->GetIsInvicible() )
	{
		return;
	}

	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( !enemys[i]->GetIsAlive() )
		{
			continue;
		}

		// プレイヤーと敵との判定
		if ( Utility::IsRectCollision(enemys[i]->GetPosX(),
									  enemys[i]->GetPosY(),
									  enemys[i]->GetWidth(),
									  enemys[i]->GetHeight(),
									  player->GetPosX(),
									  player->GetPosY(),
									  player->GetWidth(),
									  player->GetHeight()) )
		{
			player->ReceiveDamage(5, !player->GetIsLeft());
			break;
		}
	}
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
			continue;
		}

		// エネミーの攻撃とプレイヤーの当たり判定
		if ( Utility::IsCircleCollision(enemys[i]->GetAttackPosX(),
										enemys[i]->GetAttackPosY(),
										enemys[i]->GetAttackRadius() - 4,
										player->GetPosX(),
										player->GetPosY(),
										player->GetRadius() - 4) )
		{
			enemys[i]->HitAttack();
			player->ReceiveDamage(enemys[i]->GetAttackPower(),
								  enemys[i]->GetIsAttackLeftWard());
		}
	}
}

// チェックポイントの通過判定
void Chara_Manager::PassCheckPoint()
{
	// 通過フラグがTRUEの場合は処理を行わない
	if ( isPassCheckPoint )
	{
		return;
	}

	// チェックポイントを通過しているか判定
	int x = (int)player->GetPosX() / CHIP_SIZE;
	int y = (int)player->GetPosY() / CHIP_SIZE;
	if ( spawnData[y][x] == e_CharaPlayer_ChecKPoint )
	{
		isPassCheckPoint = true;
	}
}

// 更新処理
void Chara_Manager::Update(int screenX, int screenY)
{
	// プレイヤー
	player->Update();

	// プレイヤーがゴール時は処理を行わない
	if ( player->GetIsGoal() )
	{
		return;
	}

	//キャラの当たり判定
	CharaCollision();

	// エネミー
	EnemyManager(screenX, screenY);

	// 攻撃の当たり判定
	AttackCollision();

	// チェックポイントの通過判定
	PassCheckPoint();
}

// 描画処理
void Chara_Manager::Draw(float shakeX, float shakeY,
						 int scrollX, int scrollY)
{
	// プレイヤー
	player->Draw(shakeX, shakeY, scrollX, scrollY);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->Draw(shakeX, shakeY, scrollX, scrollY);
	}
}

// displaceXを設定
void Chara_Manager::SetDisplaceX(int displaceX)
{
	// プレイヤー
	player->SetDisplaceX(displaceX);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->SetDisplaceX(displaceX);
	}

	this->displaceX = displaceX;
}

// displaceXを設定
void Chara_Manager::SetDisplaceY(int displaceY)
{
	// プレイヤー
	player->SetDisplaceY(displaceY);

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		enemys[i]->SetDisplaceY(displaceY);
	}

	this->displaceY = displaceY;
}

// スクロールの中心X座標を取得
float Chara_Manager::GetScrollCenterX()
{
	return player->GetPosX();
}

// スクロールの中心Y座標を取得
float Chara_Manager::GetScrollCenterY()
{
	return player->GetPosY();
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
	if ( !player->GetIsAlive() && !player->GetIsExplosion() )
	{
		// 座標を取得
		explosionX = player->GetPosX();
		explosionY = player->GetPosY();

		player->Explosion();

		return true;
	}

	// エネミー
	for ( unsigned int i = 0; i < enemys.size(); i++ )
	{
		if ( enemys[i]->GetIsAlive() )
		{
			continue;
		}

		if ( !enemys[i]->GetIsAlive() && !enemys[i]->GetIsExplosion() )
		{
			// 座標を取得
			explosionX = enemys[i]->GetPosX();
			explosionY = enemys[i]->GetPosY();

			enemys[i]->Explosion();

			return true;
		}
	}

	return false;
}

// プレイヤーの中心X座標を取得
float Chara_Manager::GetPlayerX()
{
	return player->GetPosX();
}

// プレイヤーの中心Y座標を取得
float Chara_Manager::GetPlayerY()
{
	return player->GetPosY();
}

// プレイヤーのmoveXを取得
float Chara_Manager::GetPlayerMoveX()
{
	return player->GetMoveX();
}
// プレイヤーのmoveYを取得
float Chara_Manager::GetPlayerMoveY()
{
	return player->GetMoveY();
}

// プレイヤーのHPを取得
int Chara_Manager::GetPlayerHp()
{
	return player->GetHp();
}

// プレイヤーの最大HPを取得
int Chara_Manager::GetPlayerMaxHp()
{
	return P_MAX_HP;
}

// プレイヤーの最大バッテリーを取得
int Chara_Manager::GetPlayerBattery()
{
	return player->GetBattery();
}

// プレイヤーのバッテリーを取得
int Chara_Manager::GetPlayerMaxBattery()
{
	return P_MAX_BATTERY;
}

// プレイヤーisAliveを取得
bool Chara_Manager::GetPlayerIsAlive()
{
	return player->GetIsAlive();
}

// プレイヤーのゴールフラグを取得
bool Chara_Manager::GetPlayerIsGoal()
{
	return player->GetIsGoal();
}