#pragma once

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;			// HP�����^�C��
const int HP_CHARGE_TIME = (60 * 1) / 2;	// HP�`���[�W�^�C��

const float DASH_SPEED = 7.0f;// �_�b�V���X�s�[�h

const int PLAYER_MAX_HP = 100;	// �ő�HP

const int PLAYER_CONSUMPTION_BULLET_NUM = 5;	// �d�͂������e��

class Chara_Player:public CharaBase
{
private:
	int hpTimer;		// HP(�o�b�e���[)�^�C�}�[
	int chargeTimer;	// HP(�o�b�e���[)�`���[�W�^�C�}�[
	int shotBulletNum;	// �������e��

	bool isRelease;		// �L�[���͂��Ȃ���������true

	// �ړ�
	void Move();

	// HP(�o�b�e���[)����
	void HpDcrease();

	// HP(�o�b�e���[)�`���[�W
	void HpCharge();

	// HP�Ǘ�
	void HpManager();

public:
	Chara_Player(float x, float y, int radius,
				 float speed, int hp, int attackPower, int graphHandle);
	~Chara_Player();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(float shakeX, float shakeY);

	// �U��
	bool IsAttack();
};