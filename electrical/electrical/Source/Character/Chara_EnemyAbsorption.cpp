#include "DxLib.h"
#include "Chara_EnemyAbsorption.h"
#include "../Define/Define.h"

Chara_EnemyAbsorption::Chara_EnemyAbsorption(float x, float y, int radius,
											 float speed, int hp, int graphHandle):
	CharaEnemyBase(x, y, radius, speed, hp, graphHandle)
{

}

Chara_EnemyAbsorption::~Chara_EnemyAbsorption()
{

}

// 初期化処理
void Chara_EnemyAbsorption::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;
}

// 移動
void Chara_EnemyAbsorption::Move()
{
	moveX = 0.0f;
	moveY = 0.0f;

	// テスト用
	{
		if ( x - radius < 0 || x + radius > WIN_WIDTH )
		{
			speed *= -1;
		}

		moveX += speed;
	}

	CharaMove();
}

// 更新処理
void Chara_EnemyAbsorption::Update()
{
	if ( isAlive )
	{
		Move();
		ChangeGraphicDirection();
	}
}

// 描画処理
void Chara_EnemyAbsorption::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}