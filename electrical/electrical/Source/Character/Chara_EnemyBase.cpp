#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"
#include "../Resource/Graphic.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{

}

// ジャンプする
void Chara_EnemyBase::Jump()
{
	if ( x != oldX )
	{
		return;
	}

	// 目の前に縦1ブロックがあるかつ真上にブロックがない場合のみジャンプする
	if ( Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_NONE &&
		((Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width + 1, y - CHIP_SIZE) == e_MAP_NONE) ||
		 (Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x - width - 1, y - CHIP_SIZE) == e_MAP_NONE)) )
	{
		CharaJump();
	}
}

// 進行方向を変える
void Chara_EnemyBase::ChangeDirection()
{
	if ( x != oldX || isJump || isFall )
	{
		return;
	}

	// 進む予定の位置に縦に2つ並んでブロックがある
	if ( (Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width + 1, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x - width - 1, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1;
	}

	// 目の前に縦1ブロックがあるかつ真上にブロックがある
	if ( (Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1;
	}
}

// 画像の向きを変化
void Chara_EnemyBase::ChangeGraphicDirection()
{
	if ( x == oldX )
	{
		return;
	}

	// 左に進行で右向きの場合
	if ( !isLeftWard )
	{
		if ( speed < 0.0f )
		{
			// 左を向く
			isLeftWard = true;
		}
	}
	// 右に進行で左向きの場合
	else
	{
		if ( speed > 0.0f )
		{
			// 右を向く
			isLeftWard = false;
		}
	}
}

// プレイヤーとの間にブロックがあるか探す
bool Chara_EnemyBase::IsBlock(float playerX)
{
	// 敵とプレイヤーの間のブロック数
	int enemySpace = (int)fabsf(x - playerX) / CHIP_SIZE;

	// プレイヤーとの間にブロックがあるか
	for ( int i = 1; i <= enemySpace; i++ )
	{
		// 左向きの時
		if ( isLeftWard )
		{
			if ( Stage::GetMapParam(x - (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
		// 右向きの時
		else
		{
			if ( Stage::GetMapParam(x + (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
	}


	return false;
}

// 敵同士の当たり判定
void Chara_EnemyBase::EnemiesCollision()
{

}