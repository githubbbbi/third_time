#include "DxLib.h"
#include "Chara_EnemyGun.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../stage/stage.h"

Chara_EnemyGun::Chara_EnemyGun(float x, float y, int radius,
	float speed, int hp, int attackPower, int graphHandle) :
	Chara_EnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	shotBulletNum = 0;
	bulletInterval = 0;
	enemySpace = 0;
	blockFlag = false;
	isTargetLock = false;
}

Chara_EnemyGun::~Chara_EnemyGun()
{

}

// 初期化処理
void Chara_EnemyGun::Initialize()
{

}

void Chara_EnemyGun::Move(float playerX, float playerY, bool isPlayerAlive)
{
	//初期化
	moveX = 0.0f;
	moveY = 0.0f;
	blockFlag = false;

	//敵とプレイヤーの間のブロック数
	if ( x < playerX )
	{
		enemySpace = (playerX - x) / 64;
	}
	else
	{
		enemySpace = (x - playerX) / 64;
	}

	//右向き時のプレイヤーとの間にブロックがあるか
	for ( int i = 0; i < enemySpace; i++ )
	{
		if ( isLeftWard == FALSE )
		{
			if ( Stage::GetMapParam(x + (64 * i), y) == e_MAP_BLOCK )
			{
				blockFlag = 1;
			}
		}
		else if ( isLeftWard == TRUE )
		{
			if ( Stage::GetMapParam(x - (64 * i), y) == e_MAP_BLOCK )
			{
				blockFlag = 1;
			}
		}
	}

	// 射程内で止まる 間にブロックがあればとまらない
	if ( playerX - x + radius >= 200 || x - radius - playerX >= 200 || blockFlag )
	{
		moveX += speed;

		// 射程外では撃たない
		isTargetLock = false;

		// x座標が変わっておらず、目の前にブロックがある場合のみジャンプする
		if ( x == oldX && Stage::GetMapParam(x + radius + 1, y) == e_MAP_BLOCK
			|| Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK )
		{
			CharaJump();
		}
		
	}
	else if ( y != playerY )	//ｙが違う場合なら、射程内でも進む
	{
		moveX += speed;
		//ジャンプ
		if ( x == oldX && Stage::GetMapParam(x + radius + 1, y) == e_MAP_BLOCK
			|| Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK )
		{
			CharaJump();
		}
	}
	else
	{
		// 射程内で、y座標が同じなら撃つ
		isTargetLock = true;
	}

	// 標的になったら、プレイヤーを追いかける（反転したり）
	if ( isTargetLock )
	{
		// プレイヤーより右で、右を向いている場合、左向きに変える
		if ( playerX < x && speed > 0 )
		{
			speed *= -1;
			isLeftWard = TRUE;
		}
		else if ( playerX > x && speed < 0 )
		{
			speed *= -1;
			isLeftWard = FALSE;
		}
	}
	CharaMove(30.0f, 30.0f);
}

// 更新処理
void Chara_EnemyGun::Update(float playerX, float playerY, bool isPlayerAlive,
	float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}
}

// 描画処理
void Chara_EnemyGun::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
			1.0, 0.0, graphHandle, true, isLeftWard);
	}
}

// 攻撃ヒット
void Chara_EnemyGun::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// 攻撃処理の管理
void Chara_EnemyGun::WeaponManager(int electricGunGH)
{
	//弾のインターバルを測るカウント
	bulletInterval++;

	//インターバルの初期化
	if ( bulletInterval > BULLET_INTERVAL )
	{
		bulletInterval = 0;
	}

	// 生成
	if ( bulletInterval == BULLET_INTERVAL && isTargetLock )
	{
		electricGun.push_back(new ElectricGun(x, y,
			16, 10.0f,
			isLeftWard,
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

// 電気銃の要素数
unsigned int Chara_EnemyGun::GetGunSize()
{
	return electricGun.size();
}

// 電気銃のX座標取得
float Chara_EnemyGun::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// 電気銃のY座標取得
float Chara_EnemyGun::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// 電気銃のradius取得
int Chara_EnemyGun::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}