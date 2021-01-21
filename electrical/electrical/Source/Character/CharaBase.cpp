#include "DxLib.h"
#include <math.h>
#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

const int CHARA_SIZE = 56;
const float GRAVITY = 0.850f;
const float JUMP_POWER = -13.0f;
const int INVICIBLE_TIME = 60;

// コンストラクタ
CharaBase::CharaBase(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower)
{
	anim = new Animation;

	// 変数の初期化
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->width = width;
	this->height = height;

	this->hp = hp;
	this->attackPower = attackPower;

	oldX = x;
	oldY = y;

	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
	isFall = false;

	isAttack = false;

	r = g = b = 255.0f;
	h = 0.0f;
	s = 0.0f;
	v = 255.0f;

	state = 0;
	graphIndex = 0;

	cBlinkingTimer = 0;
	cBlinkingCounter = 0;
	isCBlinking = false;

	bBlinkingTimer = 0;
	bBlinkingCounter = 0;
	isBBlinking = false;

	isKnockBack = false;
	isAttackLeftWard = false;

	invicibleTimer = 0;
	isInvicible = false;

	blendMode = DX_BLENDMODE_NOBLEND;
	blendValue = 0;
}

// デストラクタ
CharaBase::~CharaBase()
{
	delete anim;
}

// キャラクタのジャンプ
void CharaBase::CharaJump()
{
	if ( !isJump && !isFall )
	{
		gravity = JUMP_POWER;
		isJump = true;
	}
}

// キャラクタの上昇&落下
void CharaBase::CharaRiseAndFall()
{
	// 上昇&落下
	if ( isJump || isFall )
	{
		// 落下速度を増やす
		gravity += GRAVITY;

		// 落下速度を移動量に加える
		moveY += gravity;
	}
	// ジャンプ中でも落下中でもなければジャンプさせない
	else
	{
		gravity = 0.0f;
	}
}

// キャラクタの移動
void CharaBase::CharaMove(float hitWidth, float hitHeight)
{
	// 1フレーム前の座標取得
	oldX = x;
	oldY = y;

	// 上昇&落下
	CharaRiseAndFall();

	// XまたはY方向の移動量について考慮しない場合に用いる
	float dummy = 0.0f;

	// キャラクタの左上、右上、左下、右上部分に当たり判定がある
	// マップに衝突しているか調べ、衝突していた場合補正する

	// 上下の移動量をチェック
	// 左下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x - hitWidth, y + hitHeight,
							  &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// 右下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x + hitWidth, y + hitHeight,
							  &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// 左上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x - hitWidth, y - hitHeight,
							  &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// 右上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x + hitWidth, y - hitHeight,
							  &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// 上下移動量を加える
	y += moveY;

	// 左右の移動量をチェック
	Utility::MapHitCheck(x - hitWidth, y + hitHeight, &moveX, &dummy);	// 左下
	Utility::MapHitCheck(x + hitWidth, y + hitHeight, &moveX, &dummy);	// 右下
	Utility::MapHitCheck(x - hitWidth, y - hitHeight, &moveX, &dummy);	// 左上
	Utility::MapHitCheck(x + hitWidth, y - hitHeight, &moveX, &dummy);	// 右上

	// 左右移動量を加える
	x += moveX;

	// 接地判定
	// キャラクタの左下または右下が地面であるか調べる
	if ( (Stage::GetMapParam(x - hitWidth,
							 y + hitHeight + 1.0f) == e_MAP_BLOCK ||
		  Stage::GetMapParam(x + hitWidth,
							 y + hitHeight + 1.0f) == e_MAP_BLOCK) )
	{
		// 足場がある場合、接地中
		isFall = false;
		isJump = false;
	}
	else
	{
		// 足場がない場合、落下中にする
		isFall = true;
	}
}

// HP(バッテリー)がない
void CharaBase::HpZero()
{
	if ( hp <= 0 )
	{
		hp = 0;
		isAlive = false;
	}
}

// HP管理
void CharaBase::HpManager()
{
	HpZero();
}

// 色点滅
void CharaBase::ColorBlinking(float h, float s, float v, int change, int  num)
{
	if ( isCBlinking )
	{
		// 点滅終了
		if ( cBlinkingCounter > num )
		{
			this->s = 0.0f;
			cBlinkingCounter = 0;
			cBlinkingTimer = 0;
			isCBlinking = false;

			return;
		}

		// 点滅
		cBlinkingTimer++;
		if ( cBlinkingTimer < change )
		{
			this->h = h;
			this->s = s;
			this->v = v;
		}
		else if ( cBlinkingTimer < change * 2 )
		{
			this->s = 0.0f;
			this->v = 255.0f;
		}
		else if ( cBlinkingTimer < change * 3 )
		{
			cBlinkingCounter++;
			cBlinkingTimer = 0;
		}
	}
}

// Blendについて指定された回数だけ点滅
void CharaBase::BlendBlinking(int blendMode1, int blendMode2,
							  int blendValue1, int blendValue2, int change, int num)
{
	if ( isBBlinking )
	{
		// 点滅終了
		if ( bBlinkingCounter > num )
		{
			this->blendMode = DX_BLENDMODE_NOBLEND;
			this->blendValue = 0;
			bBlinkingCounter = 0;
			bBlinkingTimer = 0;
			isBBlinking = false;

			return;
		}

		// 点滅
		bBlinkingTimer++;
		if ( bBlinkingTimer < change )
		{
			this->blendMode = blendMode1;
			this->blendValue = blendValue1;
		}
		else if ( bBlinkingTimer < change * 2 )
		{
			this->blendMode = blendMode2;
			this->blendValue = blendValue2;
		}
		else if ( bBlinkingTimer < change * 3 )
		{
			bBlinkingCounter++;
			bBlinkingTimer = 0;
		}
	}
}

// ノックバック
void CharaBase::KnockBack()
{
	if ( isKnockBack )
	{
		if ( isCBlinking )
		{
			// 初期化
			moveX = 0.0f;
			moveY = 0.0f;

			float knockBackSpeed = 0.20f;

			if ( isAttackLeftWard )
			{
				knockBackSpeed *= -1.0f;
			}
			else
			{
				knockBackSpeed *= 1.0f;
			}

			moveX += knockBackSpeed;
		}
		// 色点滅終了でノックバック終了
		else
		{
			isKnockBack = false;
		}
	}
}

// 無敵時の処理
void CharaBase::Invicible()
{
	// 色点滅が終わり次第無敵時間のカウント開始
	if ( isCBlinking || !isInvicible )
	{
		return;
	}

	BlendBlinking(DX_BLENDMODE_ALPHA, DX_BLENDMODE_ALPHA, 150, 200, 4, 5);

	invicibleTimer++;
	if ( invicibleTimer > INVICIBLE_TIME )
	{
		invicibleTimer = 0;
		isInvicible = false;
	}
}

// アニメーション
void CharaBase::LocalAnimation(const int MOTION[][4],
							   const float NORMAL_SPEED, const float DASH_SPEED)
{
	int wait = 10;
	const int num = 4;

	if ( moveX != 0.0f || moveY != 0.0f )
	{
		if ( fabsf(speed) == NORMAL_SPEED )
		{
			wait = 10;
		}
		else if ( fabsf(speed) == DASH_SPEED )
		{
			wait = 6;
		}
	}

	int *p = (int *)MOTION;
	graphIndex = anim->AnimationLoop(p, state, wait, num);
}

// ダメージを受ける
void CharaBase::ReceiveDamage(int attackPower, bool isLeftWard)
{
	hp -= attackPower;

	// 色点滅フラグTRUE
	if ( !isCBlinking )
	{
		isCBlinking = true;
	}

	// ブレンド点滅フラグTRUE
	if ( !isBBlinking )
	{
		isBBlinking = true;
	}

	// ノックバックフラグTRUE
	if ( !isKnockBack )
	{
		isAttackLeftWard = isLeftWard;
		isKnockBack = true;
	}

	// 無敵フラグTRUE
	if ( !isInvicible )
	{
		isInvicible = true;
	}
}

// X座標を取得
float CharaBase::GetPosX()
{
	return x;
}

// Y座標を取得
float CharaBase::GetPosY()
{
	return y;
}

// oldX座標を取得
float CharaBase::GetPosOldX()
{
	return oldX;
}

// oldY座標を取得
float CharaBase::GetPosOldY()
{
	return oldY;
}

float CharaBase::GetSpeed()
{
	return speed;
}

// 半径を取得
int CharaBase::GetRadius()
{
	return radius;
}

// widthを取得
int CharaBase::GetWidth()
{
	return width;
}

// heightを取得
int CharaBase::GetHeight()
{
	return height;
}

// 攻撃力を取得
int CharaBase::GetAttackPower()
{
	return attackPower;
}

// isAliveを取得
bool CharaBase::GetIsAlive()
{
	return isAlive;
}

// isLeftWardを取得
bool CharaBase::GetIsLeftWard()
{
	return isLeftWard;
}

// isInvicibleを取得
bool CharaBase::GetIsInvicible()
{
	return isInvicible;
}