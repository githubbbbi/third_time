#pragma once

#include "Animation.h"

extern const int CHARA_SIZE;		// キャラクタのサイズ
extern const float GRAVITY;			// 重力
extern const int INVICIBLE_TIME;	// 無敵時間

class CharaBase
{
private:
	Animation *anim;

protected:
	float x;				// 中心座標
	float y;				// 中心座標
	float oldX;				// 1フレーム前の座標
	float oldY;				// 1フレーム前の座標
	float moveX;			// 移動量
	float moveY;			// 移動量
	float speed;			// スピード
	float gravity;			// 落下度
	int radius;				// 半径
	int width;				// 横幅
	int height;				// 縦幅
	int hp;					// HP
	int attackPower;		// 攻撃力
	bool isAlive;			// 生存フラグ
	bool isLeftWard;		// 左向きフラグ
	bool isJump;			// ジャンプフラグ
	bool isFall;			// 落下フラグ
	bool isAttack;			// 攻撃フラグ
	float r;				// 赤色				:0~255
	float g;				// 緑色				:0~255
	float b;				// 青色				:0~255
	float h;				// 色相(hue)			:0~360
	float s;				// 彩度(saturation)	:0~255
	float v;				// 明度(value)		:0~255

	int state;				// 現在の状態(待機、走りなど)
	int graphIndex;			// 画像添え字

	int cBlinkingTimer;		// 色点滅タイマー
	int cBlinkingCounter;	// 色点滅回数カウンター
	bool isCBlinking;		// 色点滅フラグ

	int bBlinkingTimer;		// ブレンド点滅タイマー
	int bBlinkingCounter;	// ブレンド点滅回数カウンター
	bool isBBlinking;		// ブレンド点滅フラグ

	bool isKnockBack;		// ノックバックフラグ
	bool isAttackLeftWard;	// 攻撃の左向きフラグ

	int invicibleTimer;		// 無敵時間
	bool isInvicible;		// 無敵フラグ

	bool isExplosion;		// 爆発フラグ

	int blendMode;			// ブレンドモード
	int blendValue;			// ブレンド値

	// キャラクタのジャンプ
	void CharaJump(float jumpPower);

	// キャラクタの上昇&落下
	void CharaRiseAndFall();

	// キャラの移動
	void CharaMove(float hitHalfWidth, float hitHalfHeight);

	// HP(バッテリー)が0
	void HpZero();

	// HP管理
	void HpManager();

	// 色について指定された回数だけ点滅
	void ColorBlinking(float h, float s, float v, int change, int num);

	// Blendについて指定された回数だけ点滅
	void BlendBlinking(int blendMode1, int bledMode2,
					   int blendValue1, int blendValue2, int change, int num);

	// ノックバック
	void KnockBack();

	// 無敵の処理
	void Invicible();

	// アニメーション
	void LocalAnimation(const int MOTION[][4],
						const float NORMAL_SPEED, const float DASH_SPEED);

public:
	// コンストラクタ宣言
	CharaBase(float x, float y, int radius, int width, int height,
			  float speed, int hp, int attackPower);

	// デストラクタ
	~CharaBase();

	// ダメージを受ける
	void ReceiveDamage(int attackPower, bool isAttackLeftWard);

	// 爆発
	void Explosion();

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();

	// oldX座標を取得
	float GetPosOldX();

	// oldY座標を取得
	float GetPosOldY();

	// スピードを取得
	float GetSpeed();

	// 半径を取得
	int GetRadius();

	// widthを取得
	int GetWidth();

	// heightを取得
	int GetHeight();

	// 攻撃力を取得
	int GetAttackPower();

	// isAliveを取得
	bool GetIsAlive();

	// isLeftWardを取得
	bool GetIsLeftWard();

	// isInvicibleを取得
	bool GetIsInvicible();

	// isExplosionを取得
	bool GetIsExplosion();
};