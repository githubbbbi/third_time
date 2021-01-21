#pragma once

#include "CharaBase.h"

class Chara_EnemyBase:public CharaBase
{
protected:
	float attackX;			// 攻撃中心座標
	float attackY;			// 攻撃中心座標
	int attackRadius;		// 攻撃半径
	bool isAttackLeftWard;	// 攻撃左向きフラグ

	// ジャンプする
	void Jump();

	// 進行方向を変える
	void ChangeDirection();

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// プレイヤーとの間にブロックがあるか探す
	bool IsBlock(float playerX);

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower);

	virtual void Update(float playerX, float playerY, bool isPlayerAlive) = 0;
	virtual void Draw(float shakeX, float shakeY, int scrollX, int scrollY) = 0;

	virtual void HitAttack() = 0;

	float GetAttackPosX();
	float GetAttackPosY();
	int GetAttackRadius();
	bool GetIsAttackLeftWard();
};