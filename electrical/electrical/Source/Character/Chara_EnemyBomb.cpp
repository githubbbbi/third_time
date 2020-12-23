#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius,
								 float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

Chara_EnemyBomb::~Chara_EnemyBomb()
{

}

// 初期化処理
void Chara_EnemyBomb::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;
}

// 移動
void Chara_EnemyBomb::Move(float playerX, float playerY)
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
void Chara_EnemyBomb::Update(float playerX, float playerY,
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
void Chara_EnemyBomb::Draw(float shakeX, float shakeY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY),
					  1.0, 0.0, graphHandle, true, isLeftWard);
	}
}

// 攻撃処理管理
void Chara_EnemyBomb::WeaponManager(int electricGunGH)
{

}