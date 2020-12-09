#include "DxLib.h"
#include "Chara_EnemyAbsorption.h"
#include "../Define/Define.h"

Chara_EnemyAbsorption::Chara_EnemyAbsorption(int x, int y, int radius,
											 int speed, int hp, int graphHandle):
	CharaEnemyBase(x, y, radius, speed, hp, graphHandle)
{

}

Chara_EnemyAbsorption::~Chara_EnemyAbsorption()
{

}

// 初期化処理
void Chara_EnemyAbsorption::Initialize()
{
	moveX = 0;
	moveY = 0;
}

// 移動
void Chara_EnemyAbsorption::Move()
{
	moveX = 0;
	moveY = 0;

	// テスト用
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

// 更新処理
void Chara_EnemyAbsorption::Update()
{
	Move();
}

// 描画処理
void Chara_EnemyAbsorption::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}