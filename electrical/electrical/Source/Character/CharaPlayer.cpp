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
	shotBulletNum = 0;
	isRelease = false;
}

Chara_Player::~Chara_Player()
{

}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	hpTimer = 0;
	chargeTimer = 0;
	shotBulletNum = 0;
}

// 移動
void Chara_Player::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 方向キー/アナログスティックでの左右移動
	moveX += speed * (InputPad::inputX / 1000.0f);

	// それ以外での左右移動
	if ( InputPad::inputX == 0 &&
		InputPad::inputY == 0 )
	{
		// 左移動
		if ( InputKey::IsKeyInputNow(e_KEY_LEFT) ||
			InputPad::IsPadInputNow(e_PAD_LEFT) )
		{
			moveX += speed * (InputPad::inputX / 1000);
		}

		//右移動
		if ( InputKey::IsKeyInputNow(e_KEY_RIGHT) ||
			InputPad::IsPadInputNow(e_PAD_RIGHT) )
		{
			moveX += speed * (InputPad::inputX);
		}
	}

	// ダッシュ
	if ( InputKey::IsKeyInputBarrage(e_KEY_LEFT) ||
		InputKey::IsKeyInputBarrage(e_KEY_RIGHT) ||
		InputPad::IsPadInputBarrage(e_PAD_LEFT) ||
		InputPad::IsPadInputBarrage(e_PAD_RIGHT) )
	{
		speed = DASH_SPEED;
	}
	// ダッシュ入力がなければ通常スピード
	else if ( !InputKey::IsKeyInputNow(KEY_INPUT_LEFT) &&
			 !InputKey::IsKeyInputNow(KEY_INPUT_RIGHT) &&
			 !InputPad::IsPadInputNow(PAD_INPUT_LEFT) &&
			 !InputPad::IsPadInputNow(PAD_INPUT_RIGHT) )
	{
		speed = NORMAL_SPEED;
	}

	// --- やったこと ---//
	// Chara_Player.hにbool型のisReleaseを作って、2段ジャンプを防いだ
	// InputKey::frameCountがstaticで宣言されてるから、関数使わずに呼び出してる
	// frameCountの関数はInputKey.hに用意はしてるから、必要だったら関数にしてね
	// フレームの最大値とフレームを割る値の変数を作ってないから、作ってほしい（どこに作ればいいかわからなくてできてない）
	// 一応、バランスみながら今の値にいてるけど、調整してもらって勝手に変えて全然いいよ

	// ジャンプ
	if ( InputKey::IsKeyInputNow(e_KEY_JUMP) ||
		InputPad::IsPadInputNow(e_PAD_JUMP) )
	{
		// ジャンプの初期化
		if ( !isJump )
		{
			InputKey::frameCount[e_KEY_JUMP] = 0; // InputKey::ResetFrame(e_KEY_JUMP)でもできる
			isRelease = false;
			isJump = true;
		}

		// ジャンプの更新処理
		if ( isJump )
		{
			InputKey::frameCount[e_KEY_JUMP]++;

			// キーが離ていなければ、フレームカウントを掛けた値を代入する
			if ( !isRelease && InputKey::frameCount[e_KEY_JUMP] < 3 )
			{
				gravity += JUMP_POWER * (0.6 - (InputKey::frameCount[e_KEY_JUMP] / 10));
			}
			else if ( !isRelease && InputKey::frameCount[e_KEY_JUMP] < 9)
			{
				gravity += JUMP_POWER * 0.1;
			}
		}
	}
	// ジャンプ中にキーが離された時の処理（2段ジャンプの阻止)
	else if ( InputKey::IsKeyInputRelease(e_KEY_JUMP) ||
			InputPad::IsPadInputRelease(e_PAD_JUMP) )
	{
		if ( isJump )
		{
			isRelease = true;
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

	// 撃った弾数が一定数を超える
	if ( shotBulletNum >= PLAYER_CONSUMPTION_BULLET_NUM )
	{
		// HP減少
		hp -= 2;
		shotBulletNum = 0;
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
			else if ( chargeTimer < 60 * 9 )
			{
				chargeTimer += 3;
			}
			else if ( chargeTimer < 60 * 12 )
			{
				chargeTimer += 5;
			}
			else
			{
				chargeTimer += 6;
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

	// 0以下にもならない
	if ( hp < 0 )
	{
		hp = 0;
	}
}

// 攻撃
bool Chara_Player::IsAttack()
{
	// 死亡時は攻撃できない
	if ( !isAlive )
	{
		return false;
	}

	if ( InputKey::IsKeyInputTrigger(e_KEY_ATTACK) ||
		InputPad::IsPadInputTrigger(e_PAD_ATTACK) )
	{
		// 撃った弾数を増やす
		shotBulletNum++;
		return true;
	}

	return false;
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		// チャージ中は動けない
		if ( chargeTimer <= 0 )
		{
			Move();
		}

		HpManager();

		// 向き固定ボタンが押されていない
		if ( !InputKey::IsKeyInputNow(e_KEY_FIXED_DIRECTION) &&
			!InputPad::IsPadInputNow(e_PAD_FIXED_DIRECTION) )
		{
			ChangeGraphicDirection();
		}
	}
}

// 描画処理
void Chara_Player::Draw(float shakeX, float shakeY)
{
	// プレイヤー
	if ( isAlive )
	{
		DrawRotaGraph((int)(x + shakeX), (int)(y + shakeY), 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// デバッグ用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "inputPadX:%d%", InputPad::inputX);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "frameCount:%.2f", InputKey::frameCount[e_KEY_JUMP]);
}