#include "DxLib.h"
#include <algorithm>
#include "Chara_EnemyElectric.h"
#include "../Define/Define.h"
#include"../Character/Chara_Manager.h"
#include"../Stage/Stage.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

const int EE_WIDTH = 50;
const int EE_HEIGHT = 50;
const float EE_NORMAL_SPEED = 2.0f;
const int EE_BULLET_INTERVAL = 70;
const int EE_MOTION[e_EE_STATE_NUM][4] =
{
	{  0,  1,  2,  3 },
	{  4,  5,  6,  7 },
	{  8,  9, 10, 11 },
	{ 12, 13, 14, 15 }
};

Chara_EnemyElectric::Chara_EnemyElectric(float x, float y, int radius, int width, int height,
										 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	Chara_EnemyBase(x, y, radius, width, height, speed, hp, attackPower, mapChipX, mapChipY)
{
	shotBulletNum = 0;
	bulletInterval = 0;
	shotLength = 0;
	isTargetLock = false;
}

Chara_EnemyElectric::~Chara_EnemyElectric()
{
	// 電気銃
	for ( int i = electricGun.size() - 1; i >= 0; i-- )
	{
		delete electricGun[i];
		electricGun.erase(electricGun.begin() + i);
	}
}

// 自動移動
void Chara_EnemyElectric::AutoMove(float playerX, float playerY, bool isPlayerAlive)
{
	if ( isKnockBack )
	{
		return;
	}

	// 初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 爆弾エネミーと同じくマップチップでの座標に
	int enemyMapY = (int)y / CHIP_SIZE;
	int playerMapY = (int)playerY / CHIP_SIZE;

	if ( isPlayerAlive )
	{
		if ( shotLength == 0 )
		{
			shotLength = GetRand(150) + 100;
		}

		// 射程内で止まる 間にブロックがあればとまらない
		if ( fabsf(playerX - x + radius) >= shotLength || IsBlock(playerX) )
		{
			moveX += speed;

			// 射程外では撃たない

			isTargetLock = false;

			// ジャンプ
			Jump();
		}
		// ｙが違う場合なら、射程内でも進む
		else if ( enemyMapY != playerMapY )
		{
			moveX += speed;

			// 射程外では撃たない
			isTargetLock = false;
		}
		else
		{
			// 射程内で、y座標が同じなら撃つ
			isTargetLock = true;
		}

		// 標的になったら、プレイヤーを追いかける（反転したり)
		if ( isTargetLock )
		{
			// プレイヤーより右で、右を向いている場合、左向きに変える
			if ( playerX < x && !isLeftWard )
			{
				speed *= -1;
				if ( speed < 0 )
				{
					isLeftWard = true;
				}
			}

			if ( playerX > x && isLeftWard )
			{
				speed *= -1;
				if ( speed > 0 )
				{
					isLeftWard = false;
				}
			}
		}
	}

	// 動いている場合こうげきしていない
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		isAttack = false;
	}

	// プレイヤーが死んでる場合は、弾撃たない
	if ( !isPlayerAlive )
	{
		isTargetLock = false;
	}
}

// 移動
void Chara_EnemyElectric::Move(float playerX, float playerY,
							   int screenX, int screenY, bool isPlayerAlive)
{
	ChangeDirection(screenX, screenY);
	AutoMove(playerX, playerY, isPlayerAlive);
	CharaMove((float)width / 2.0f, (float)height / 2.0f);
}

// 攻撃処理の管理
void Chara_EnemyElectric::WeaponManager()
{
	// 弾のインターバルを測るカウント
	if ( isAlive )
	{
		bulletInterval++;
	}

	// インターバルの初期化
	if ( bulletInterval > EE_BULLET_INTERVAL || isCBlinking )
	{
		bulletInterval = 0;
	}

	// 生成
	if ( bulletInterval == EE_BULLET_INTERVAL && isTargetLock )
	{
		// 飛距離
		float flightDistance = 100.0f;
		electricGun.push_back(new Weapon_ElectricGun(x, y + 8.0f,
													 16,
													 EG_SPEED, 0.0f,
													 flightDistance, 2,
													 isLeftWard));
		isAttack = true;
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
			// 攻撃座標をリセット
			attackX = 0.0f;
			attackY = 0.0f;

			delete electricGun[i];
			electricGun.erase(electricGun.begin() + i);
		}

	}
}

// 攻撃管理
void Chara_EnemyElectric::AttackManager(float playerX, float playerY, bool isPlayerAlive)
{
	if ( !isPlayerAlive )
	{
		return;
	}

	// プレイヤーと一番距離が近いものを並べ替え、先頭にもってくる
	std::sort(electricGun.begin(), electricGun.end(),
			  [playerX, playerY](Weapon_ElectricGun *a, Weapon_ElectricGun *b)
	{
		return fabsf(playerX - a->GetPosX()) < fabsf(playerX - b->GetPosX()) &&
			fabsf(playerY - a->GetPosY()) < fabsf(playerY - b->GetPosY());
	});

	if ( electricGun.size() <= 0 )
	{
		return;
	}

	attackX = electricGun[0]->GetPosX();
	attackY = electricGun[0]->GetPosY();
	attackRadius = electricGun[0]->GetRadius();
	isAttackLeftWard = electricGun[0]->GetIsLeftWard();
}

// 状態
void Chara_EnemyElectric::State()
{
	// 待機
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		// 歩き
		state = e_EE_STATE_WALK;
	}

	// ジャンプ
	if ( isJump || isFall )
	{
		state = e_EE_STATE_JUMP;
	}

	// 攻撃
	if ( isAttack )
	{
		state = e_EE_STATE_ATTACK;
	}

	// ダメーを受ける(色点滅中)
	if ( isCBlinking )
	{
		state = e_EE_STATE_RECIEVE_DAMAGE;
	}
}

// 更新処理
void Chara_EnemyElectric::Update(float playerX, float playerY,
								 int screenX, int screenY, bool isPlayerAlive)
{
	if ( isAlive )
	{
		Move(playerX, playerY, screenX, screenY, isPlayerAlive);
		ChangeGraphicDirection();
		HpZero();
		ColorBlinking(0.0f, 255.0f, 255.0f, 5, 2);
		KnockBack();
		State();
		Animation(EE_MOTION, EE_NORMAL_SPEED, 0.0f);
	}

	WeaponManager();
	AttackManager(playerX, playerY, isPlayerAlive);

	// HSVからRGBに変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// 描画処理
void Chara_EnemyElectric::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	// 電気銃
	for ( unsigned int i = 0; i < electricGun.size(); i++ )
	{
		electricGun[i]->Draw(scrollX, scrollY, displaceX, displaceY);
	}

	if ( isAlive )
	{
		SetDrawBlendMode(blendMode, blendValue);
		SetDrawBright((int)r, (int)g, (int)b);
		DrawRotaGraph((int)(x + shakeX) - scrollX + displaceX,
					  (int)(y + shakeY) - scrollY + displaceY,
					  1.0, 0.0, Graphic::GetInstance()->GetEnemyElectric(graphIndex), true, isLeftWard);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 攻撃ヒット
void Chara_EnemyElectric::HitAttack()
{
	if ( electricGun.size() <= 0 )
	{
		return;
	}

	electricGun[0]->Hit();
}