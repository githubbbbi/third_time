#include "Chara_EnemyBase.h"

CharaEnemyBase::CharaEnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

bool CharaEnemyBase::GetIsAlive()
{
	return isAlive;
}

// ƒ_ƒ[ƒW‚ğó‚¯‚é
void CharaEnemyBase::ReceiveDamage(int playerAttackPower)
{
	hp -= playerAttackPower;
}