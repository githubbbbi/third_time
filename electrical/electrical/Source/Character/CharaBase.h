#pragma once

const float GRAVITY = 0.8f;			// 重力
const float JUMP_POWER = -13.0f;	// ジャンプ力

class CharaBase
{
protected:
	float x;			// 中心座標
	float y;			// 中心座標
	float oldX;			// 1フレーム前の座標
	float oldY;			// 1フレーム前の座標
	float moveX;		// 移動量
	float moveY;		// 移動量
	float speed;		// スピード
	float gravity;		// 落下度
	int radius;			// 半径
	int width;			// 横幅
	int height;			// 縦幅
	int graphHandle;	// 画像ハンドル
	int hp;				// HP
	int attackPower;	// 攻撃力
	bool isAlive;		// 生存フラグ
	bool isLeftWard;	// 左向きフラグ
	bool isJump;		// ジャンプフラグ
	bool isFall;		// 落下フラグ
	float r;			// 赤色				:0~255
	float g;			// 緑色				:0~255
	float b;			// 青色				:0~255
	float h;			// 色相(hue)			:0~360
	float s;			// 彩度(saturation)	:0~255
	float v;			// 明度(value)		:0~255

	// キャラクタの落下
	void CharaFall();

	// キャラの移動
	void CharaMove(float hitWidth, float hitHeight);

	// HP(バッテリー)が0
	void HpZero();

	// HP管理
	void HpManager();

	// 指定された回数だけ点滅
	void Blinking(float h, float s, float v, int noOfTimes);

public:
	// コンストラクタ宣言
	CharaBase(float x, float y, int radius, int width, int height,
			  float speed, int hp, int attackPower, int graphHandle);

	void CharaJump();

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

	// ダメージを受ける
	void ReceiveDamage(int attackPower);

	// キャラクタ同士が接触
	void CharactersCollision();
};