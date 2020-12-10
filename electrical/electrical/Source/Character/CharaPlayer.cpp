#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(float x, float y, int radius,
						   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;

	bulletGraphHandle = LoadGraph("Resource/Graphic/Bullet/bullet.png");
}

Chara_Player::~Chara_Player()
{

}

// 弾構造体のコンストラクタ
Chara_Player::Bullet::Bullet(float x, float y, int radius, float speed, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->speed = speed;
	this->graphHandle = graphHandle;

	isAlive = true;
}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	hpTimer = 0;
	chargeTimer = 0;
}

// 移動
void Chara_Player::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

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
		// ジャンプ中でない
		if ( !isJump )
		{
			gravity = JUMP_POWER;
			isJump = true;
		}
	}

	CharaMove();

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
void Chara_Player::HpCharge()
{
	// 移動中でない
	if ( moveX == 0.0f && moveY == 0.0f && !isJump )
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

			// HP上昇
			if ( chargeTimer % HP_CHARGE_TIME == 0 )
			{
				hp++;
			}

			// チャージ中はHPは減少しない
			hpTimer = 0;

			return;
		}
	}

	chargeTimer = 0;
}

// HP管理
void Chara_Player::HpManager()
{
	HpDcrease();
	HpCharge();
	HpZero();

	// HPは最大値を超えない
	if ( hp > PLAYER_MAX_HP )
	{
		hp = 100;
	}
}

// 攻撃
void Chara_Player::Attack()
{
	if ( InputKey::IsKeyInputTrigger(e_KEY_ATTACK) ||
		InputPad::IsPadInputTrigger(e_PAD_ATTACK) )
	{
		bullets.push_back(new Bullet(x, y, 16, 15, bulletGraphHandle));
	}
}

// 弾の更新処理
void Chara_Player::Bullet::Update()
{
	x -= speed;

	if ( x + radius<0 ||
		x - radius > WIN_WIDTH )
	{
		isAlive = false;
	}
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		HpManager();
		Attack();
		ChangeGraphicDirection();

		// 弾
		for ( int i = 0; i < bullets.size(); i++ )
		{
			bullets[i]->Update();
		}
	}
}

// 描画処理
void Chara_Player::Draw()
{
	// 弾
	for ( int i = 0; i < bullets.size(); i++ )
	{
		if ( bullets[i]->isAlive )
		{
			DrawRotaGraph((int)bullets[i]->x, (int)bullets[i]->y,
						  1.0, 0.0, bullets[i]->graphHandle, true);
		}
	}

	// プレイヤー
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// デバッグ用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
}