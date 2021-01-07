#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int graphHandle):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, graphHandle)
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
void Chara_EnemyBomb::Move(float playerX, float playerY, bool isPlayerAlive)
{
	moveX = 0.0f;
	moveY = 0.0f;

	// 移動処理
	// 敵とプレイヤーのX座標が等しい時、スピードをダッシュに合わせる
	if ( isPlayerAlive && !IsBlock(playerX) &&
		(y == playerY && isLeftWard && playerX < x ||
		 y == playerY && !isLeftWard && playerX > x) )
	{
		if ( speed > 0 )
		{
			speed = DASH_SPEED;
		}
		else
		{
			speed = -DASH_SPEED;
		}
	}
	// 違う時、スピードをノーマルに戻す
	else
	{
		if ( speed > 0 )
		{
			speed = NORMAL_SPEED;
		}
		else
		{
			speed = -NORMAL_SPEED;
		}

		// 進む予定の位置に2つ並んでブロックがあった場合、方向を変える
		if ( Stage::GetMapParam(x + radius + 2, y) == e_MAP_BLOCK &&
			Stage::GetMapParam(x + radius + 2, y - CHIP_SIZE) == e_MAP_BLOCK ||
			Stage::GetMapParam(x - radius - 2, y) == e_MAP_BLOCK &&
			Stage::GetMapParam(x - radius - 2, y - CHIP_SIZE) == e_MAP_BLOCK )
		{
			speed *= -1;
		}

		// X座標に変化がなくなった時にジャンプする
		if ( x == oldX )
		{
			CharaJump();
		}
	}

	moveX += speed;

	CharaMove((float)width, (float)height);
}

// 更新処理
void Chara_EnemyBomb::Update(float playerX, float playerY, bool isPlayerAlive,
							 float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ShakeStart(&*shakeAddX, &*shakeAddY);
	}
}

// 描画処理
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
	}
}

// 攻撃ヒット
void Chara_EnemyBomb::HitAttack(float *shakeAddX, float *shakeAddY)
{
	if ( isAlive )
	{
		hp = 0;
	}
}