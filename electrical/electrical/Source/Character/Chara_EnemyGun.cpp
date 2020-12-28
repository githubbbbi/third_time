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
	targetlock = 0;
}

Chara_EnemyGun::~Chara_EnemyGun()
{

}

// 初期化処理
void Chara_EnemyGun::Initialize()
{

}

// 移動処理
void Chara_EnemyGun::Move(float playerX, float playerY)
{
	moveX = 0.0f;
	moveY = 0.0f;

	//壁反射
	if ( x - radius < 0 || x + radius > WIN_WIDTH )
	{
		speed *= -1;
	}

	//射程内で止まる
	if ( playerX - x + radius >= 200 || x - radius - playerX >= 200  )
	{
		moveX += speed;
		//射程外では撃たない
		targetlock = 0;

		// ジャンプするとき
		if ( x == oldX )
		{
			CharaJump();
		}
	}
	//else
	{
		//射程内で、y座標が同じなら撃つ
		targetlock = 1;

	}


	//標的になったら、プレイヤーを追いかける（反転したり）
	if ( targetlock == 1 )
	{
		//プレイヤーより右で、右を向いている場合、左向きに変える
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




	//// 画面外に行きそうなとき、進む予定の位置に2つ並んでブロックがあった場合、方向を変える
	//if ( x - radius < 0 || x + radius > WIN_WIDTH ||
	//	Stage::GetMapParam(x + radius + 1, y) == e_MAP_BLOCK &&
	//	Stage::GetMapParam(x + radius + 1, y - CHIP_SIZE) == e_MAP_BLOCK ||
	//	Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK &&
	//	Stage::GetMapParam(x - radius - 2, y - CHIP_SIZE) == e_MAP_BLOCK )
	//{
	//	speed *= -1;
	//}
	//


	// ここまで
	CharaMove();
}

// 更新処理
void Chara_EnemyGun::Update(float playerX, float playerY,
	float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY);
		ChangeGraphicDirection();
		HpZero();
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}
}

// 描画処理
void Chara_EnemyGun::Draw(float shakeX, float shakeY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw();
	}

	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY),
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
	// ここに
	// 電気銃の更新処理

	// 生成
	//
	if ( bulletInterval == 70 && targetlock == 1 )
	{
		electricGun.push_back(new ElectricGun(x,
			y,
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
	//弾のインターバルを測るカウント
	bulletInterval++;

	//インターバルの初期化
	if ( bulletInterval > 70 )
	{
		bulletInterval = 0;
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


