#include "Chara_EnemyBase.h"

CharaEnemyBase::CharaEnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

// �V�F�C�N�X�^�[�g
void CharaEnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp == 0 )
	{
		*shakeAddX = *shakeAddY = 6.0f;
	}
}