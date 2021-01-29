#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_ElectricGun.h"

enum EnemyElectricState
{
	e_EE_STATE_WALK,				// 歩き
	e_EE_STATE_JUMP,				// ジャンプ
	e_EE_STATE_ATTACK,				// 攻撃
	e_EE_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_EE_STATE_NUM
};

extern const int EE_WIDTH;						// 横幅
extern const int EE_HEIGHT;						// 縦幅
extern const float EE_NORMAL_SPEED;				// 通常スピード
extern const int EE_BULLET_INTERVAL ;			// 間隔
extern const int EE_MOTION[e_EE_STATE_NUM][4];	// モーション

class Chara_EnemyElectric:public Chara_EnemyBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int shotBulletNum;		// 撃った弾数
	int bulletInterval;		// 銃を撃つ間隔
	int shotLength;
	bool isTargetLock;		// 範囲内のフラグ

	// 自動移動
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// 移動
	void Move(float playerX, float playerY,
			  int screenX, int screenY, bool isPlayerAlive);

	// 武器処理管理
	void WeaponManager();

	// 攻撃管理
	void AttackManager(float playerX, float playerY, bool isPlayerAlive);

	// 状態
	void State();

public:
	Chara_EnemyElectric(float x, float y, int radius, int width, int height,
						float speed, int hp, int attackPower, int mapChipX, int mapChipY);
	~Chara_EnemyElectric();

	// 更新処理
	void Update(float playerX, float playerY,
				int screenX, int screenY, bool isPlayerAlive) override;

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY) override;

	// 攻撃ヒット
	void HitAttack() override;
};