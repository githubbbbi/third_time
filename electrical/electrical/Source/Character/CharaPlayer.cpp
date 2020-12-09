#include "DxLib.h"
#include "Chara_Player.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(int x, int y, int radius,
						   int speed, int hp, int graphHandle):
	CharaBase(x, y, radius, speed, hp, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;
}

Chara_Player::~Chara_Player()
{

}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0;
	moveY = 0;

	hpTimer = 0;
	chargeTimer = 0;
}

// 移動
void Chara_Player::Move()
{
	// 移動量初期化
	moveX = 0;
	moveY = 0;

	// 左移動
	if ( InputKey::IsKeyInputNow(e_KEY_LEFT) ||
		InputPad::IsPadInputNow(e_PAD_LEFT) )
	{
		moveX -= speed;
	}

	//右移動
	if ( InputKey::IsKeyInputNow(e_KEY_RIGHT) ||
		InputPad::IsPadInputNow(e_PAD_RIGHT) )
	{
		moveX += speed;
	}

	// ジャンプ
	if ( InputKey::IsKeyInputNow(e_KEY_JUMP) ||
		InputPad::IsPadInputNow(e_PAD_JUMP) )
	{
		isJump = true;
	}

	// 移動量加算
	x += moveX;
	y += moveY;

	// 画面内にとどまる(X方向についてのみ)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// HP(バッテリー)減少
void Chara_Player::HpDcrease()
{
	hpTimer++;
	if ( hpTimer > HP_DCREASE_TIME )
	{
		// HP減少
		hp--;

		// タイマーリセット
		hpTimer = 0;
	}
}

// HP(バッテリー)チャージ
bool Chara_Player::HpCharge()
{
	if ( InputKey::IsKeyInputNow(e_KEY_ATTACK) ||
		InputPad::IsPadInputNow(e_PAD_ATTACK) )
	{
		// 一定時間チャージでチャージ量が増加
		if ( chargeTimer < 60 * 3 )
		{
			chargeTimer++;
		}
		else if ( chargeTimer < 60 * 6 )
		{
			chargeTimer += 2;
		}
		else
		{
			chargeTimer += 3;
		}

		if ( chargeTimer % HP_CHARGE_TIME == 0 )
		{
			// HP上昇
			hp++;
		}

		// チャージ中はHPは減少しない
		hpTimer = 0;

		return true;
	}

	chargeTimer = 0;

	return false;
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		// チャージ中は移動不可
		if ( !HpCharge() )
		{
			Move();
		}

		ChangeGraphicDirection();
		HpDcrease();

		// HPは最大値を超えない
		if ( hp > MAX_HP )
		{
			hp = 100;
		}
	}
}

// 描画処理
void Chara_Player::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// デバッグ用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d 攻撃ボタン長押しでチャージ", hp);
}