#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Stage/Stage.h"

// コンストラクタ
CharaBase::CharaBase(float x, float y, int radius,
					 float speed, int hp, int attackPower, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->graphHandle = graphHandle;

	this->hp = hp;
	this->attackPower = attackPower;

	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
}

// キャラクタの落下
void CharaBase::CharaFall()
{
	// 落下(画面外では落下しない)
	if ( isJump )
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
void CharaBase::CharaMove()
{
	// 落下
	CharaFall();

	// ダミー これはXまたはY方向の移動量について考慮しない場合に用いる
	float dummy = 0.0f;

	// キャラクタの左上、右上、左下、右上部分に当たり判定がある
	// マップに衝突しているか調べ、衝突していた場合補正する

	// 上下の移動量をチェック
	// 左下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x - radius, y + radius, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = 0.0f;
	}

	// 右下 ブロックの上辺に着地した場合、落下停止
	if ( Utility::MapHitCheck(x + radius, y + radius, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = 0.0f;
	}

	// 左上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x - radius, y - radius, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = GRAVITY;
	}

	// 右上 ブロックの下辺に衝突した場合、落下
	if ( Utility::MapHitCheck(x + radius, y - radius, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = GRAVITY;
	}

	// 上下移動量を加える
	y += moveY;

	// 左右の移動量をチェック
	Utility::MapHitCheck(x - radius, y + radius, &moveX, &dummy);	// 左下
	Utility::MapHitCheck(x + radius, y + radius, &moveX, &dummy);	// 右下
	Utility::MapHitCheck(x - radius, y - radius, &moveX, &dummy);	// 左上
	Utility::MapHitCheck(x + radius, y - radius, &moveX, &dummy);	// 右上

	// 左右移動量を加える
	x += moveX;

	// 接地判定
	// キャラクタの左下と右下の下に地面があるか調べる
	if ( Stage::GetMapParam(x - radius, y + radius + 1.0f) != e_MAP_BLOCK &&
		Stage::GetMapParam(x + radius, y + radius + 1.0f) != e_MAP_BLOCK )
	{
		// 足場がない場合、ジャンプ中にする
		isJump = true;
	}
	else if ( gravity > 0.0f )
	{
		// 足場がある場合、接地中
		isJump = false;
	}
}

// 画像の向きを変化
void CharaBase::ChangeGraphicDirection()
{
	// 左に進行
	if ( moveX < 0.0f )
	{
		isLeftWard = true;
	}
	// 右に進攻
	else if ( moveX > 0.0f )
	{
		isLeftWard = false;
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

// 半径を取得
int CharaBase::GetRadius()
{
	return radius;
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