#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"
#include "../Resource/Sound_SE.h"

const int P_WIDTH = 30;
const int P_HEIGHT = 50;
const float P_NORMAL_SPEED = 3.0f;
const float P_DASH_SPEED = 5.0f;
const float P_JUMP_POWER = -15.0f;
const int BATTERY_DCREASE_TIME = 60 * 1;
const int BATTERY_CHARGE_TIME = 60 * 1;
const int P_MAX_HP = 100;
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
	{ 36, 37, 38, 39 },
	{ 40, 41, 42, 43 },
	{ 44, 45, 46, 47 }
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
	isBatteryZero = false;

	batteryBox.boxPosLeft = 0.0f;
	batteryBox.boxPosRight = 0.0f;
	batteryBox.boxPosTop = 0.0f;
	batteryBox.boxPosBottom = 0.0f;
	batteryBox.r = 255.0f;
	batteryBox.g = 255.0f;
	batteryBox.b = 255.0f;
	batteryBox.h = 210.0f;
	batteryBox.s = 230.0f;
	batteryBox.v = 200.0f;
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

// 移動入力があるかの判定
bool Chara_Player::IsInputMove()
{
	return (padInputX != 0 || padInputY != 0);
}

// ダッシュの判定
bool Chara_Player::IsDash()
{
	return (InputManager::IsInputBarrage(e_MOVE_LEFT) ||
			InputManager::IsInputBarrage(e_MOVE_RIGHT)) &&
		!InputManager::IsInputNow(e_FIXED);
}

// ダッシュなどの判定からスピードを取得
float Chara_Player::GetNowSpeed()
{
	// ダッシュ
	if ( IsDash() )
	{
		return P_DASH_SPEED;
	}

	// 通常移動
	if ( IsInputMove() )
	{
		return P_NORMAL_SPEED;
	}

	return 0.0f;
}

// 向き固定時の処理
void Chara_Player::Fixed()
{
	// 向き固定が押されているかつ後ろ向きに進行する場合はspeedを遅くする
	if ( InputManager::IsInputNow(e_FIXED) )
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
}

// 入力での移動
void Chara_Player::InputMove()
{
	// ノックバック時は動けない
	if ( isKnockBack )
	{
		return;
	}

	// バッテリーがゼロの時は動けない
	if ( isBatteryZero )
	{
		moveX = 0.0f;
		moveY = 0.0f;

		return;
	}

	// ゴールした後は動けない
	if ( IsGoal() )
	{
		moveX = 0.0f;
		moveY = 0.0f;

		return;
	}

	// 初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// パッドレバーの入力情報を取得
	padInputX = InputManager::GetPadInputX();
	padInputY = InputManager::GetPadInputY();

	// スピード
	speed = GetNowSpeed();

	// 向き固定時
	Fixed();

	// 方向キー/アナログスティックでの左右移動
	moveX += speed * (padInputX / 1000.0f);

	// ジャンプ
	if ( InputManager::IsInputTrigger(e_JUMP) )
	{
		// SE再生
		Sound_SE::GetInstance()->PlaySE(e_PLAYER_JUMP_SE, false);

		// ジャンプの初期化
		CharaJump(P_JUMP_POWER);
	}

	// ジャンプ上昇中中にキーが離された場合ジャンプを中止
	if ( isJump && gravity < P_JUMP_POWER / 2.0f )
	{
		if ( InputManager::IsInputNo(e_JUMP) )
		{
			gravity = P_JUMP_POWER / 1.5f;
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
	// ゴールした後は処理を行わない
	if ( IsGoal() )
	{
		return;
	}

	// ダメージを受けているときは処理を行わない
	if ( isCBlinking )
	{
		batteryTimer = 0;
		return;
	}

	// 移動中
	if ( moveX != 0.0f || moveY != 0.0f || isJump || isFall )
	{
		// 歩き
		if ( fabsf(speed) == P_NORMAL_SPEED )
		{
			batteryTimer++;
		}
		// ダッシュ
		else
		{
			batteryTimer += 3;
		}

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
		battery -= 5;
		shotBulletNum = 0;
	}
}

// バッテリチャージを行わない場合
void Chara_Player::NotBatteryChage()
{
	// SE停止
	Sound_SE::GetInstance()->StopSE(e_PLAYER_CHAGING_SE);
	batteryChargeTimer = 0;
}

// バッテリーチャージ
void Chara_Player::BatteryCharge()
{
	// ゴールした後は処理を行わない
	if ( IsGoal() )
	{
		return;
	}

	// バッテリー中だったがバッテリーが最大になったとき
	if ( batteryChargeTimer > 0 && battery == P_MAX_BATTERY )
	{
		NotBatteryChage();
		return;
	}

	// バッテリーが最大になったときは処理を行わない
	if ( battery == P_MAX_BATTERY )
	{
		NotBatteryChage();
		return;
	}

	// ダメージを受けたときは処理を行わない
	if ( isCBlinking )
	{
		NotBatteryChage();
		return;
	}

	// 移動中は処理を行わない
	if ( moveX != 0.0f || moveY != 0.0f ||
		isJump || isFall )
	{
		NotBatteryChage();
		return;
	}

	// 攻撃中は処理を行わない
	if ( isAttack )
	{
		NotBatteryChage();
		return;
	}

	// ここからチャージ処理
	// SE再生
	Sound_SE::GetInstance()->PlaySE(e_PLAYER_CHAGING_SE, true);
	batteryChargeTimer += 15;

	// バッテリー上昇
	if ( batteryChargeTimer % BATTERY_CHARGE_TIME == 0 )
	{
		battery++;
	}

	// チャージ中はバッテリーは減少しない
	batteryTimer = 0;

	return;
}

// バッテリーゼロ
void Chara_Player::BatteryZero()
{
	if ( !isBatteryZero )
	{
		return;
	}

	// 一度バッテリーがゼロになると
	// バッテリーが最大になるまでゼロフラグは解除されない
	if ( battery == P_MAX_BATTERY )
	{
		isBatteryZero = false;
	}
}

// バッテリー管理
void Chara_Player::BatteryManager()
{
	BatteryDecrease();
	BatteryCharge();
	BatteryZero();

	// バッテリーは最大値を超えない
	if ( battery > P_MAX_BATTERY )
	{
		battery = 100;
	}

	// 0以下にもならない
	if ( battery < 0 )
	{
		battery = 0;
		isBatteryZero = true;
	}
}

// 攻撃
bool Chara_Player::IsAttack()
{
	// 死亡時または攻撃を受けているときまたはバッテリーゼロの時は攻撃できない
	if ( !isAlive || isCBlinking || isBatteryZero )
	{
		return false;
	}

	// ゴール時は攻撃できない
	if ( IsGoal() )
	{
		return false;
	}

	if ( InputManager::IsInputTrigger(e_ATTACK) )
	{
		// 撃った弾数を増やす
		shotBulletNum++;
		attackMotionFrame = 0;

		// 充電しない
		batteryChargeTimer = 0;

		isAttack = true;

		return true;
	}

	return false;
}

// 攻撃処理の管理
void Chara_Player::WeaponManager()
{
	// 生成
	if ( IsAttack() && isAlive )
	{
		int xx = 24;
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

// ゴールに入っているかの判定
bool Chara_Player::IsGoal()
{
	float dummy = 0.0f;
	const int hitHalfWidth = P_WIDTH / 2;
	const int hitHalfHeight = P_HEIGHT / 2;

	// 一か所でも含まれていないとreturn
	// 左下
	if ( Utility::MapHitCheck(x - hitHalfWidth, y + hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// 右下
	if ( Utility::MapHitCheck(x + hitHalfWidth, y + hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// 左上
	if ( Utility::MapHitCheck(x - hitHalfWidth, y - hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	// 右上
	if ( Utility::MapHitCheck(x + hitHalfWidth, y - hitHalfHeight,
							  &dummy, &dummy) != e_HIT_GOAL )
	{
		return false;
	}

	return true;
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

	// バッテリーゼロ
	if ( isBatteryZero )
	{
		state = e_P_STATE_BATTERY_ZERO;
	}

	// ダメーを受ける(色点滅中)
	if ( isCBlinking )
	{
		state = e_P_STATE_RECIEVE_DAMAGE;
	}

	// ゴール
	if ( IsGoal() )
	{
		state = e_P_STATE_GOAL;
	}
}

// バッテリーボックスの更新処理
void Chara_Player::BatteryBoxUpdate()
{
	// 左向き
	if ( isLeftWard )
	{
		batteryBox.boxPosLeft = x + 1.0f;
	}
	// 右向き
	else
	{
		batteryBox.boxPosLeft = x - 19.0f;
	}

	batteryBox.boxPosRight = batteryBox.boxPosLeft + 18.0f;
	batteryBox.boxPosTop = y + 18.0f - 30.0f * ((float)battery / (float)P_MAX_BATTERY);
	batteryBox.boxPosBottom = y + 18.0f;

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&batteryBox.r, &batteryBox.g, &batteryBox.b,
							 batteryBox.h, batteryBox.s, batteryBox.v);
}

// バッテリーボックスの描画処理
void Chara_Player::BatteryBoxDraw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	DrawBox((int)(batteryBox.boxPosLeft + shakeX) - scrollX,
			(int)(batteryBox.boxPosTop + shakeY) - scrollY,
			(int)(batteryBox.boxPosRight + shakeX) - scrollX,
			(int)(batteryBox.boxPosBottom + shakeY) - scrollY,
			GetColor((int)batteryBox.r, (int)batteryBox.g, (int)batteryBox.b), true);
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

		// バッテリー
		BatteryBoxUpdate();

		// 向き固定ボタンが押されていない
		if ( !InputManager::IsInputNow(e_FIXED) )
		{
			ChangeGraphicDirection();
		}

		Animation(P_MOTION, P_NORMAL_SPEED, P_DASH_SPEED);
	}

	WeaponManager();

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

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		// バッテリー
		BatteryBoxDraw(shakeX, shakeY, scrollX, scrollY);

		// プレイヤー
		DrawRotaGraph((int)(x + shakeX) - scrollX, (int)(y + shakeY) - scrollY,
					  1.0, 0.0, Graphic::GetInstance()->GetPlayer(graphIndex), true, isLeftWard);

		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 攻撃ヒット
void Chara_Player::HitAttack(int index)
{
	electricGun[index]->Hit();
}

// スポーン
void Chara_Player::Spawn(float x, float y)
{
	this->x = x;
	this->y = y;
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

// HPを取得
int Chara_Player::GetHp()
{
	return hp;
}

// バッテリーを取得
int Chara_Player::GetBattery()
{
	return battery;
}

// ゴール判定を取得
bool Chara_Player::GetIsGoal()
{
	return IsGoal();
}