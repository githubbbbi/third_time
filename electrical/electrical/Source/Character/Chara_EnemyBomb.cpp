#include "DxLib.h"
#include "Chara_EnemyBomb.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EB_WIDTH = 50;
const int EB_HEIGHT = 50;
const float EB_NORMAL_SPEED = 1.0f;
const float EB_DASH_SPEED = 8.0f;
const int EB_MOTION[e_EB_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 }
};

Chara_EnemyBomb::Chara_EnemyBomb(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
{

}

// 自動移動
void Chara_EnemyBomb::AutoMove(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isKnockBack )
	{
		return;
	}

	// 初期化
	moveX = 0.0f;
	moveY = 0.0f;

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
			speed = EB_DASH_SPEED;
		}
		else
		{
			speed = -EB_DASH_SPEED;
		}

		isAttack = true;
	}
	// 違う時、スピードをノーマルに戻す
	else
	{
		if ( speed > 0 )
		{
			speed = EB_NORMAL_SPEED;
		}
		else
		{
			speed = -EB_NORMAL_SPEED;
		}

		isAttack = false;

		// ジャンプ
		Jump();
	}

	moveX += speed;
}

// 移動
void Chara_EnemyBomb::Move(float playerX, float playerY, bool isPlayerAlive)
{
	ChangeDirection();
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// 攻撃管理
void Chara_EnemyBomb::AttackManager(bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	if ( isAttack )
	{
		attackX = x;
		attackY = y;
		attackRadius = radius;
		isAttackLeftWard = isLeftWard;
	}
	else
	{
		attackX = 0.0f;
		attackY = 0.0f;
	}
}

// 状態
void Chara_EnemyBomb::State()
{
	// 歩き
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		state = e_EB_STATE_WALK;
	}

	// ジャンプ
	if ( isJump || isFall )
	{
		state = e_EB_STATE_JUMP;
	}

	// 攻撃
	if ( isAttack )
	{
		state = e_EB_STATE_ATTACK;
	}

	// ダメーを受ける(色点滅中)
	if ( isCBlinking )
	{
		state = e_EB_STATE_RECIEVE_DAMAGE;
	}
}

// 更新処理
void Chara_EnemyBomb::Update(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, isPlayerAlive);
		AttackManager(isPlayerAlive);
		ChangeGraphicDirection();
		HpManager();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EB_MOTION, EB_NORMAL_SPEED, EB_DASH_SPEED);
	}

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyBomb::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyBomb(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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