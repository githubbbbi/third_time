#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

// コンストラクタ
CharaBase::CharaBase(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->width = width;
	this->height = height;
	this->graphHandle = graphHandle;

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

// キャラクタの落下
void CharaBase::CharaFall()
{
	// 落下
	if ( isJump || isFall )
	{
		// 落下速度を増やす
		gravity += GRAVITY;

		// 落下速度を移動量に加える
		moveY += gravity;
	}
	// ジャンプ中でなければジャンプさせない
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

	// 落下
	CharaFall();

	// ダミー これはXまたはY方向の移動量について考慮しない場合に用いる
	float dummy = 0.0f;

	// キャラクタの左上、右上、左下、右上部分に当たり判定がある
	// マップに衝突しているか調べ、衝突していた場合補正する

	// 上下の移動量をチェック
	// 左下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x - hitWidth, y + hitHeight, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// 右下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x + hitWidth, y + hitHeight, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// 左上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x - hitWidth, y - hitHeight, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// 右上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x + hitWidth, y - hitHeight, &dummy, &moveY) == e_HIT_BOTTOM )
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
	if ( Stage::GetMapParam(x - hitWidth, y + hitHeight + 1.0f) == e_MAP_BLOCK ||
		Stage::GetMapParam(x + hitWidth, y + hitHeight + 1.0f) == e_MAP_BLOCK )
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
		isAlive = false;
	}
}

// HP管理
void CharaBase::HpManager()
{
	HpZero();
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

// ダメージを受ける
void CharaBase::ReceiveDamage(int attackPower)
{
	hp -= attackPower;
}

// 敵と敵でない場合のキャラクタ同士が接触
void CharaBase::CharactersCollision()
{
	moveX = 0.0f;
}