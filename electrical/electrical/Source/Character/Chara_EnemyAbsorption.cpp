#include "DxLib.h"
#include "Chara_EnemyAbsorption.h"
#include "../Define/Define.h"

Chara_EnemyAbsorption::Chara_EnemyAbsorption(int x, int y, int speed,
											 int radius, int graphHandle):
	CharaEnemyBase(x, y, speed, radius, graphHandle)
{

}

Chara_EnemyAbsorption::~Chara_EnemyAbsorption()
{

}

// ����������
void Chara_EnemyAbsorption::Initialize()
{
	moveX = 0;
	moveY = 0;
}

// �ړ�
void Chara_EnemyAbsorption::Move()
{
	moveX = 0;
	moveY = 0;

	// �e�X�g�p
	{
		if ( x - radius < 0 || x + radius > WIN_WIDTH )
		{
			speed *= -1;
		}

		moveX += speed;
	}

	ChangeGraphicDirection();

	x += moveX;
	y += moveY;
}

// �X�V����
void Chara_EnemyAbsorption::Update()
{
	Move();
}

// �`�揈��
void Chara_EnemyAbsorption::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}