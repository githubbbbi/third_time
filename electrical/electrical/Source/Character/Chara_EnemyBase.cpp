#include "Chara_EnemyBase.h"
#include"../stage/stage.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	blockFlag = false;
	enemySpace = 0.0f;
}

// シェイクスタート
void Chara_EnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp == 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

//敵の当たり判定
void Chara_EnemyBase::EnemiesCollision()
{

}

// ブロックが間にあるか探す
void Chara_EnemyBase::FindBlock(float playerX)
{
	//敵とプレイヤーの間のブロック数
	if (x < playerX)
	{
		enemySpace = (playerX - x) / CHIP_SIZE;
	}
	else
	{
		enemySpace = (x - playerX) / CHIP_SIZE;
	}

	//右向き時のプレイヤーとの間にブロックがあるか
	for (int i = 0; i < enemySpace; i++)
	{
		if (isLeftWard == false)
		{
			if (Stage::GetMapParam(x + (64 * i), y) == e_MAP_BLOCK)
			{
				blockFlag = true;
			}
		}
		else if (isLeftWard == false)
		{
			if (Stage::GetMapParam(x - (64 * i), y) == e_MAP_BLOCK)
			{
				blockFlag = true;
			}
		}
	}
}
