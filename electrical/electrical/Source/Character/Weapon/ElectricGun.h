#pragma once

class ElectricGun
{
private:
	float x;				// ���S���W
	float y;				// ���S���W
	float moveX;			// �ړ���
	float moveY;			// �ړ���
	int radius;				// ���a
	float speed;			// �X�s�[�h
	int graphHandle;		// �摜�n���h��
	int hitFrame;			// �q�b�g���Ă���t���[����
	bool isAlive;			// ���˃t���O
	bool isMapHit;			// �}�b�v�q�b�g�t���O
	bool isCharaLeftWard;	// �L�����N�^�̍������t���O

public:
	ElectricGun(float x, float y, int radius,
				float speed, bool isCharaLeftWard, int graphHandle);

	// �u���b�N�Ƃ̓����蔻����l�������ړ�
	void Move();

	// ����
	void Erase();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

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
};