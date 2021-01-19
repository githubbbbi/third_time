#pragma once

class WeaponBase
{
protected:
	float x;				// ���S���W
	float y;				// ���S���W
	float oldX;				// 1�t���[���O�̒��S���W
	float oldY;				// 1�t���[���O�̒��S���W
	float moveX;			// �ړ���
	float moveY;			// �ړ���
	int radius;				// ���a
	float speedX;			// �X�s�[�hX
	float speedY;			// �X�s�[�hY
	int mapHitFrame;			// �}�b�v�`�b�v�Ƀq�b�g���Ă���t���[����
	int eraseFrame;			// �}�b�v�`�b�v�Ƀq�b�g���Ă����������t���[����
	bool isAlive;			// ���˃t���O
	bool isMapHit;			// �}�b�v�q�b�g�t���O
	bool isLeftWard;		// �������t���O

	// �}�b�v�`�b�v�Ƃ̓����蔻����l�������ړ�
	void BulletMove();

public:
	WeaponBase(float x, float y, int radius, float speedX, float speedY,
			   int eraseFrame, bool isCharaLeftWard);


	// �e���q�b�g�����ꍇ�̏���
	void Hit();

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// ���a���擾
	int GetRadius();

	// isAlive���擾
	bool GetIsAlive();

	// isLeftWard���擾
	bool GetIsLeftWard();
};