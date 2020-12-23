#include "Chara_EnemyBase.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius,
							   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

// �V�F�C�N�X�^�[�g
void Chara_EnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp == 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

//�G�̓����蔻��
void Chara_EnemyBase::EnemiesCollision()
{
	
	x -= speed;
	speed *= -1;
}