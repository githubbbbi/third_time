#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Utility/Utility.h"

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

	// 座標をマップチップでの座標に変換
	int enemyMapY = (int)y / CHIP_SIZE;
	int playerMapY = (int)playerY / CHIP_SIZE;

	// 移動処理
	// 敵とプレイヤーのy座標が等しい時、スピードをダッシュに合わせる
	if ( isPlayerAlive && !IsBlock(playerX) &&
		(enemyMapY == playerMapY) &&
		(isLeftWard && x > playerX || !isLeftWard && x < playerX) )
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
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// 更新処理
void Chara_EnemyBomb::Update(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ColorBlinking(0.0f, 255.0f, 255.0f, 2);
	}

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, graphHandle, true, isLeftWard);
		SetDrawBright(255, 255, 255);
	}
}

// 攻撃ヒット(突進)
void Chara_EnemyBomb::HitAttack()
{
	if ( isAlive )
	{
		hp = 0;
	}
}