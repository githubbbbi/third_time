#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(float x, float y, int radius,
						   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;
	shotBulletNum = 0;
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

	// パッドレバーの入力情報を取得
	static int padInputX, padInputY;
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// 方向キー/アナログスティックでの左右移動
	moveX += speed * (padInputX / 1000.0f);

	// それ以外での左右移動
	if ( InputManager::GetPadInputX == 0 &&
		InputManager::GetPadInputY == 0 )
	{
		// 左移動
		if ( InputManager::IsInputNow(e_MOVE_LEFT) )
		{
			moveX += speed * (padInputX / 1000);
		}

		//右移動
		if ( InputManager::IsInputNow(e_MOVE_RIGHT) )
		{
			moveX += speed * (padInputX);
		}
	}

	// ダッシュ
	if ( InputManager::IsInputBarrage(e_MOVE_LEFT) ||
		InputManager::IsInputBarrage(e_MOVE_RIGHT) )
	{
		speed = DASH_SPEED;
	}
	// ダッシュ入力がなければ通常スピード
	else if ( !InputManager::IsInputNow(e_MOVE_LEFT) &&
			 !InputManager::IsInputNow(e_MOVE_RIGHT) )
	{
		speed = NORMAL_SPEED;
	}

	// ジャンプ
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// ジャンプの初期化
		if ( !isJump && !isFall )
		{
			gravity = JUMP_POWER;
			isJump = true;
		}
	}

	// ジャンプ上昇中中にキーが離された場合ジャンプを中止
	if ( isJump && gravity < 0.0f )
	{
		if ( InputManager::IsInputNot(e_JUMP) )
		{
			gravity = JUMP_POWER / 2.0f;
			isJump = false;
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
		if ( InputManager::IsInputNow(e_ATTACK) )
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

	if ( InputManager::IsInputTrigger(e_ATTACK) )
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
		if ( !InputManager::IsInputNow(e_FIXED_DIRECTION) )
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
}