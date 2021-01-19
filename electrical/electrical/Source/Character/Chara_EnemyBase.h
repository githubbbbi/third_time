#pragma once

#include "CharaBase.h"
#include "Animation.h"

enum EnemyState
{
	e_E_STATE_IDLE,					// 待機
	e_E_STATE_WALK,					// 歩き
	e_E_STATE_JUMP,					// ジャンプ
	e_E_STATE_ATTACK,				// 攻撃
	e_E_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_E_STATE_NUM
};

extern const int E_MOTION[e_E_STATE_NUM][4];	// エネミーのモーション

class Chara_EnemyBase:public CharaBase
{
private:
	Animation *anim;

protected:
	// ジャンプする
	void Jump();

	// 進行方向を変える
	void ChangeDirection();

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// プレイヤーとの間にブロックがあるか探す
	bool IsBlock(float playerX);

	// 状態
	void State();

	// アニメーション
	void LocalAnimation();

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower);
};