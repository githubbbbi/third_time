#pragma once

#include "CharaBase.h"


extern const float E_JUMP_POWER;	// ジャンプ力

class Chara_EnemyBase:public CharaBase
{
protected:
	int mapChipX;			// マップチップ上X座標
	int mapChipY;			// マップチップ上Y座標
	float attackX;			// 攻撃中心座標
	float attackY;			// 攻撃中心座標
	int attackRadius;		// 攻撃半径
	bool isAttackLeftWard;	// 攻撃左向きフラグ

	// ジャンプする
	void Jump();

	// 進行方向を変える
	void ChangeDirection(int screenX, int screenY);

	// 画像の向きを変化
	void ChangeGraphicDirection();

	// プレイヤーとの間にブロックがあるか探す
	bool IsBlock(float playerX);

public:
	Chara_EnemyBase(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int mapChipX, int mapChipY);

	virtual ~Chara_EnemyBase() = default;

	virtual void Update(float playerX, float playerY,
						int screenX, int screenY, bool isPlayerAlive) = 0;
	virtual void Draw(float shakeX, float shakeY, int scrollX, int scrollY) = 0;

	virtual void HitAttack() = 0;

	int GetMapChipX();
	int GetMapChipY();
	float GetAttackPosX();
	float GetAttackPosY();
	int GetAttackRadius();
	bool GetIsAttackLeftWard();
};