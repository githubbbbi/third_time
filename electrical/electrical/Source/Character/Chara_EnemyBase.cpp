#include "Chara_EnemyBase.h"

CharaEnemyBase::CharaEnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

// シェイクスタート
void CharaEnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp == 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

//敵の当たり判定
void CharaEnemyBase::EnemiesCollision()
{
	
	x -= speed;
	speed *= -1;
}
