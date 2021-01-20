#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

enum EnemyWaterState
{
	e_EW_STATE_IDLE,				// ‘Ò‹@
	e_EW_STATE_ATTACK,				// UŒ‚
	e_EW_STATE_RECIEVE_DAMAGE,		// ƒ_ƒ[ƒW‚ğó‚¯‚é
	e_EW_STATE_NUM
};

extern const int EW_WIDTH;						// ‰¡•
extern const int EW_HEIGHT;						// c•
extern const int EW_BULLET_INTERVAL;			// ŠÔŠu
extern const int EW_MOTION[e_EW_STATE_NUM][4];	// ƒ‚[ƒVƒ‡ƒ“

class Chara_EnemyWater:public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// e‚ğŒ‚‚ÂŠÔŠu
	float bulletSpeed;		// e‚ÌƒXƒs[ƒh

	// ˆÚ“®
	void Move();

	// Œü‚«‚ğ•ÏX
	void ChangeDirection(float playerX);

	// ó‘Ô
	void State();

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower);
	~Chara_EnemyWater();

	// ‰Šú‰»ˆ—
	void Initialize();

	// XVˆ—
	void Update(float playerX, float playerY);

	// •`‰æˆ—
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// UŒ‚ƒqƒbƒg
	void HitAttack(int index);

	// •Šíˆ—ŠÇ—
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive);

	// …’e‚Ì—v‘f”
	unsigned int GetGunSize();

	// …’e‚ÌXÀ•Wæ“¾
	float GetGunPosX(int index);

	// …’e‚ÌYÀ•Wæ“¾
	float GetGunPosY(int index);

	// …’e‚Ìradiusæ“¾
	int GetGunRadius(int index);

	// …e‚ÌisLeftWardæ“¾
	bool GetIsGunLeftWard(int index);
};