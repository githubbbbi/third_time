#pragma once

class ElectricGun
{
private:
	float x;			// ���S���W
	float y;			// ���S���W
	int radius;			// ���a
	float speed;		// �X�s�[�h
	int graphHandle;	// �摜�n���h��
	bool isAlive;		// ���˃t���O

public:
	ElectricGun(float x, float y, int radius,
				float speed, int graphHandle);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// �e���q�b�g�����ꍇ�̏���
	void BulletHit();

	// X���W���擾
	float GetPosX();

	// Y���W���擾
	float GetPosY();

	// ���a���擾
	int GetRadius();

	// isAlive���擾
	bool GetIsAlive();
};