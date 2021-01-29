#pragma once

#include "Chara_EnemyBase.h"

enum EnemyBombState
{
	e_EB_STATE_WALK,				// 歩き
	e_EB_STATE_JUMP,				// ジャンプ
	e_EB_STATE_ATTACK,				// 攻撃
	e_EB_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_EB_STATE_NUM
};

extern const int EB_WIDTH;						// 横幅
extern const int EB_HEIGHT;						// 縦幅
extern const float EB_NORMAL_SPEED;				// 通常スピード
extern const float EB_DASH_SPEED;				// ダッシュスピード
extern const int EB_MOTION[e_EB_STATE_NUM][4];	// モーション

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// 自動移動
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// 移動
	void Move(float playerX, float playerY,
			  int screenX, int screenY, bool isPlayerAlive);

	// 攻撃管理
	void AttackManager(bool isPlayerAlive);

	// 状態
	void State();

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int mapChipX, int mapChipY);
	~Chara_EnemyBomb() = default;

	// 更新処理
	void Update(float playerX, float playerY,
				int screenX, int screenY, bool isPlayerAlive) override;

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	// 攻撃ヒット
	void HitAttack() override;
};