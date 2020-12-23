#include "DxLib.h"
#include "Chara_EnemyGun.h"
#include "../Define/Define.h"

Chara_EnemyGun::Chara_EnemyGun(float x, float y, int radius, 
							   float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

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

	// ここから
	{
		if ( x - radius < 0 || x + radius > WIN_WIDTH )
		{
			speed *= -1;
		}

		moveX += speed;

		// ジャンプするとき
		CharaJump();
	}
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