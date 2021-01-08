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
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 進行方向チェンジ
	ChangeDirection();

	// 移動処理
	// 敵とプレイヤーのX座標が等しい時、スピードをダッシュに合わせる
	if ( isPlayerAlive && !IsBlock(playerX) &&
		(y == playerY && isLeftWard && playerX < x ||
		 y == playerY && !isLeftWard && playerX > x) )
	{
		if ( speed > 0 )
		{
			speed = E_BOMB_DASH_SPEED;
		}
		else
		{
			speed = -E_BOMB_DASH_SPEED;
		}
	}
	// 違う時、スピードをノーマルに戻す
	else
	{
		if ( speed > 0 )
		{
			speed = E_BOMB_NORMAL_SPEED;
		}
		else
		{
			speed = -E_BOMB_NORMAL_SPEED;
		}

		// ジャンプ
		Jump();
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