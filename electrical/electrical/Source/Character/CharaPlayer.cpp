#include "DxLib.h"
#include "Chara_Player.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(int x, int y, int speed,
								 int radius, int graphHandle):
	CharaBase(x, y, speed, radius, graphHandle)
{
}

Chara_Player::~Chara_Player()
{

}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0;
	moveY = 0;
}

// 移動
void Chara_Player::Move()
{
	// 移動量初期化
	moveX = 0;
	moveY = 0;

	// 左移動
	if ( InputKey::IsKeyInputNow(KEY_INPUT_LEFT) ||
		InputPad::IsPadInputNow(PAD_INPUT_LEFT) )
	{
		moveX -= speed;
	}

	//右移動
	if ( InputKey::IsKeyInputNow(KEY_INPUT_RIGHT) ||
		InputPad::IsPadInputNow(PAD_INPUT_RIGHT) )
	{
		moveX += speed;
	}

	// ジャンプ
	if ( InputKey::IsKeyInputNow(KEY_INPUT_UP) ||
		InputPad::IsPadInputNow(PAD_INPUT_A) )
	{
		isJump = true;
	}

	// 移動量加算
	x += moveX;
	y += moveY;

	// 画面内にとどまる(X方向についてのみ)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		ChangeGraphicDirection();
	}
}

// 描画処理
void Chara_Player::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}