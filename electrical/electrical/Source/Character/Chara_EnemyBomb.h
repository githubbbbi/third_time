#pragma once

#include "Chara_EnemyBase.h"

const int E_BOMB_WIDTH = 30;			// ����
const int E_BOMB_HEIGHT = 30;			// �c��
const float E_BOMB_NORMAL_SPEED = 2.0f;	// �ʏ�X�s�[�h
const float E_BOMB_DASH_SPEED = 8.0f;	// �_�b�V���X�s�[�h

class Chara_EnemyBomb:public Chara_EnemyBase
{
private:
	// �ړ�
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyBomb(float x, float y, int radius, int width, int height,
					float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyBomb();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float playerX, float playerY, bool isPlayerAlive,
				float *shakeAddX, float *shakeAddY);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �U���q�b�g
	void HitAttack(float *shakeAddX, float *shakeAddY);
};