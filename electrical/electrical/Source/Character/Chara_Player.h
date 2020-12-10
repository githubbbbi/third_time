#pragma once

#include "CharaBase.h"

const int HP_DCREASE_TIME = 60 * 1;			// HP�����^�C��
const int HP_CHARGE_TIME = (60 * 1) / 2;	// HP�`���[�W�^�C��

const int PLAYER_MAX_HP = 100;

class Chara_Player:public CharaBase
{
private:
	int hpTimer;		// HP(�o�b�e���[)�^�C�}�[
	int chargeTimer;	// HP(�o�b�e���[)�`���[�W�^�C�}�[

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
	void Draw();

	// �U��
	bool IsAttack();
};