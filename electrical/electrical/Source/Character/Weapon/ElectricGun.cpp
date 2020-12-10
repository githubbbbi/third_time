#include "DxLib.h"
#include "ElectricGun.h"
#include "../../Define/Define.h"

ElectricGun::ElectricGun(float x, float y, int radius,
						 float speed, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->graphHandle = graphHandle;

	isAlive = true;
}

// �X�V����
void ElectricGun::Update()
{
	x -= speed;

	if ( x + radius < 0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}
}

// �`�揈��
void ElectricGun::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y,
					  1.0, 0.0, graphHandle, true);
	}
}

// �e���q�b�g�����ꍇ�̏���
void ElectricGun::BulletHit()
{
	isAlive = false;
}

// X���W���擾
float ElectricGun::GetPosX()
{
	return x;
}

// Y���W���擾
float ElectricGun::GetPosY()
{
	return y;
}

// ���a���擾
int ElectricGun::GetRadius()
{
	return radius;
}

bool ElectricGun::GetIsAlive()
{
	return isAlive;
}