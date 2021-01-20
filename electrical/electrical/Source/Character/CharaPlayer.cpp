#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int P_WIDTH = 50;
const int P_HEIGHT = 50;
const float P_NORMAL_SPEED = 3.0f;
const float P_DASH_SPEED = 5.0f;
const int BATTERY_DCREASE_TIME = 60 * 1;
const int BATTERY_CHARGE_TIME = 60 * 1;
const int P_MAX_BATTERY = 100;
const int P_CONSUMPTION_BULLET_NUM = 5;
const int P_MOTION[e_P_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 },
	{ 16, 17, 18, 19 },
	{ 20, 21, 22, 23 },
	{ 24, 25, 26, 27 },
	{ 28, 29, 30, 31 },
	{ 32, 33, 34, 35 },
	{ 36, 37, 38, 39 }
};

Chara_Player::Chara_Player(float x, float y, int radius, int width, int height,
						   float speed, int hp, int attackPower):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{
	padInputX = 0;
	padInputY = 0;
	battery = 100;
	batteryTimer = 0;
	batteryChargeTimer = 0;
	shotBulletNum = 0;
	attackMotionFrame = 0;
}

Chara_Player::~Chara_Player()
{
	// 電気銃
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	batteryTimer = 0;
	batteryChargeTimer = 0;
	shotBulletNum = 0;
}

// 入力での移動
void Chara_Player::InputMove()
{
	if ( isKnockBack )
	{
		return;
	}

	// 初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// パッドレバーの入力情報を取得
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// ダッシュ
	if ( (InputManager::IsInputBarrage(e_MOVE_LEFT) ||
		  InputManager::IsInputBarrage(e_MOVE_RIGHT)) &&
		!InputManager::IsInputNow(e_FIXED_DIRECTION) )
	{
		speed = P_DASH_SPEED;
	}
	else if ( padInputX != 0 || padInputY != 0 )
	{
		speed = P_NORMAL_SPEED;
	}

	// 向き固定が押されているかつ後ろ向きに進行する場合はspeedを遅くする
	if ( InputManager::IsInputNow(e_FIXED_DIRECTION) )
	{
		// 左向き
		if ( isLeftWard )
		{
			// 左進行
			if ( padInputX < 0 )
			{
				speed = P_NORMAL_SPEED;
			}
			// 右進行
			else if ( padInputX > 0 )
			{
				speed = P_NORMAL_SPEED / 2.0f;
			}
		}
		// 右向き
		else
		{
			// 左進行
			if ( padInputX < 0 )
			{
				speed = P_NORMAL_SPEED / 2.0f;
			}
			// 右進行
			else if ( padInputX > 0 )
			{
				speed = P_NORMAL_SPEED;
			}
		}
	}

	// 方向キー/アナログスティックでの左右移動
	moveX += speed * (padInputX / 1000.0f);

	// ジャンプ
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// ジャンプの初期化
		CharaJump();
	}

	// ジャンプ上昇中中にキーが離された場合ジャンプを中止
	if ( isJump && gravity < JUMP_POWER / 2.0f )
	{
		if ( InputManager::IsInputNo(e_JUMP) )
		{
			gravity = JUMP_POWER / 1.5f;
			isJump = false;
		}
	}
}

// 移動
void Chara_Player::Move()
{
	InputMove();
	CharaMove((float)width / 2.0f, (float)height / 2.0f);

	// 画面内にとどまる(X方向についてのみ)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// 画像の向きを変更
void Chara_Player::ChangeGraphicDirection()
{
	// 左向き
	if ( padInputX < 0 )
	{
		isLeftWard = true;
	}
	// 右向き
	else if ( padInputX > 0 )
	{
		isLeftWard = false;
	}
}

// バッテリー減少
void Chara_Player::BatteryDecrease()
{
	// 移動中
	if ( moveX != 0.0f || moveY != 0.0f || isJump || isFall )
	{
		batteryTimer++;
		if ( batteryTimer > BATTERY_DCREASE_TIME )
		{
			// バッテリー減少
			battery--;

			// タイマーリセット
			batteryTimer = 0;
		}

		batteryChargeTimer = 0;
	}

	// 撃った弾数が一定数を超える
	if ( shotBulletNum >= P_CONSUMPTION_BULLET_NUM )
	{
		// バッテリー減少
		battery -= 2;
		shotBulletNum = 0;
	}
}

// バッテリーチャージ
void Chara_Player::BatteryCharge()
{
	if ( battery == P_MAX_BATTERY )
	{
		batteryChargeTimer = 0;
		return;
	}

	// 移動中でない
	if ( moveX == 0.0f && moveY == 0.0f && (!isJump || !isFall) )
	{
		const int charge = 60;
		// 一定時間チャージでチャージ量が増加
		if ( batteryChargeTimer < charge * 3 )
		{
			batteryChargeTimer++;
		}
		else if ( batteryChargeTimer < charge * 6 )
		{
			batteryChargeTimer += 2;
		}
		else if ( batteryChargeTimer < charge * 9 )
		{
			batteryChargeTimer += 3;
		}
		else if ( batteryChargeTimer < charge * 12 )
		{
			batteryChargeTimer += 5;
		}
		else
		{
			batteryChargeTimer += 6;
		}

		// バッテリー上昇
		if ( batteryChargeTimer % BATTERY_CHARGE_TIME == 0 )
		{
			battery++;
		}

		// チャージ中はバッテリーは減少しない
		batteryTimer = 0;

		return;
	}
}

// バッテリー管理
void Chara_Player::BatteryManager()
{
	BatteryDecrease();
	BatteryCharge();

	// バッテリーは最大値を超えない
	if ( battery > P_MAX_BATTERY )
	{
		battery = 100;
	}

	// 0以下にもならない
	if ( battery < 0 )
	{
		battery = 0;
	}
}

// 攻撃モーション
void Chara_Player::AttackMotion()
{
	if ( !isAttack )
	{
		return;
	}

	if ( attackMotionFrame++ > 30 )
	{
		attackMotionFrame = 0;
		isAttack = false;
	}
}

// 状態
void Chara_Player::State()
{
	// 待機
	if ( moveX == 0.0f && moveY == 0.0f )
	{
		state = e_P_STATE_IDLE;
	}
	else
	{
		// 歩き
		if ( fabsf(speed) == P_NORMAL_SPEED )
		{
			state = e_P_STATE_WALK;
		}
		// ダッシュ
		else
		{
			state = e_P_STATE_DASH;
		}
	}

	// 充電
	if ( batteryChargeTimer > BATTERY_CHARGE_TIME )
	{
		state = e_P_STATE_CHARGE;
	}

	// ジャンプ
	if ( isJump || isFall )
	{
		state = e_P_STATE_JUMP;
	}

	// 攻撃
	if ( isAttack )
	{
		if ( moveX == 0.0f )
		{
			state = e_P_STATE_STOP_ATTACK;
		}
		else
		{
			// 歩き
			if ( fabsf(speed) == P_NORMAL_SPEED )
			{
				state = e_P_STATE_WALK_ATTACK;
			}
			// ダッシュ
			else
			{
				state = e_P_STATE_DASH_ATTACK;
			}
		}

		// ジャンプ
		if ( isJump || isFall )
		{
			state = e_P_STATE_JUMP_ATTACK;
		}
	}

	// ダメーを受ける(色点滅中)
	if ( isCBlinking )
	{
		state = e_P_STATE_RECIEVE_DAMAGE;
	}
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		BatteryManager();
		HpManager();
		AttackMotion();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		Invicible();
		State();

		// 向き固定ボタンが押されていない
		if ( !InputManager::IsInputNow(e_FIXED_DIRECTION) )
		{
			ChangeGraphicDirection();
		}

		LocalAnimation(P_MOTION, P_NORMAL_SPEED);
	}

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_Player::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY);
	}

	// プレイヤー
	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetPlayer(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// デバッグ用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "hp:%d%", hp);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "battery:%d%", battery);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "gravity:%f%", gravity);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "moveX:%f%", moveX);
	DrawFormatString(80, 160, GetColor(255, 255, 255), "r:%f", r);
	DrawFormatString(80, 180, GetColor(255, 255, 255), "g:%f", g);
	DrawFormatString(80, 200, GetColor(255, 255, 255), "b:%f", b);
	DrawFormatString(80, 240, GetColor(255, 255, 255), "h:%f", h);
	DrawFormatString(80, 260, GetColor(255, 255, 255), "s:%f", s);
	DrawFormatString(80, 280, GetColor(255, 255, 255), "v:%f", v);
	DrawFormatString(80, 300, GetColor(255, 255, 255), "invicibleTimer:%d", invicibleTimer);
	DrawFormatString(80, 320, GetColor(255, 255, 255), "blendMode:%d", blendMode);

	DrawFormatString((int)x - scrollX, (int)y - 40 - scrollY, GetColor(255, 255, 255), "x:%.2f,y+height:%.2f", x, y + height);
	//DrawFormatString((int)x - scrollX, (int)y - 40 - scrollY, GetColor(255, 255, 255), "attackMotionFrame:%d", attackMotionFrame);
}

// 攻撃
bool Chara_Player::IsAttack()
{
	// 死亡時または攻撃を受けているときは攻撃できない
	if ( !isAlive || isCBlinking )
	{
		return false;
	}

	if ( InputManager::IsInputTrigger(e_ATTACK) )
	{
		// 撃った弾数を増やす
		shotBulletNum++;
		batteryChargeTimer = 0;
		attackMotionFrame = 0;

		isAttack = true;

		return true;
	}

	return false;
}

// 攻撃ヒット
void Chara_Player::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// 攻撃処理の管理
void Chara_Player::WeaponManager()
{
	// 生成
	if ( IsAttack() && isAlive )
	{
		int xx = 16;
		if ( isLeftWard )
		{
			xx *= -1;
		}

		electricGun.push_back(new Weapon_ElectricGun(x + xx, y,
													 16,
													 EG_SPEED,
													 0.0f, 2,
													 isLeftWard));
	}

	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Update();
	}

	// 電気銃削除
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		if ( !electricGun[i]->GetIsAlive() )
		{
			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}
	}
}

// 電気銃の要素数
unsigned int Chara_Player::GetGunSize()
{
	return electricGun.size();
}

// 電気銃のX座標取得
float Chara_Player::GetGunPosX(int index)
{
	return electricGun[index]->GetPosX();
}

// 電気銃のY座標取得
float Chara_Player::GetGunPosY(int index)
{
	return electricGun[index]->GetPosY();
}

// 電気銃のradius取得
int Chara_Player::GetGunRadius(int index)
{
	return electricGun[index]->GetRadius();
}

// 電気銃のisLeftWard取得
bool Chara_Player::GetIsGunLeftWard(int index)
{
	return electricGun[index]->GetIsLeftWard();
}