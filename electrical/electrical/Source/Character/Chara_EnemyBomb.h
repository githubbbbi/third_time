#pragma once

#include "Chara_EnemyBase.h"

extern const int E_BOMB_WIDTH;			// ����
extern const int E_BOMB_HEIGHT;			// �c��
extern const float E_BOMB_NORMAL_SPEED;	// �ʏ�X�s�[�h
extern const float E_BOMB_DASH_SPEED;	// �_�b�V���X�s�[�h

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// �����ړ�
	void AutoMove(float playerX, float playerY, bool isPlayerAlive);

	// �ړ�
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U���q�b�g
	void HitAttack();
};