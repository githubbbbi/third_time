#pragma once

class Effect_Explosion
{
private:
	float x;			// ���S���W
	float y;			// ���S���W
	float speed;		// �X�s�[�h
	double exRate;		// �g�嗦
	double randAngle;	// �p�x
	int frame;			// �t���[����
	int blendValue;		// �u�����h�l
	int blendDecrease;	// �u�����h�����l
	bool isActive;		// TRUE�̏ꍇ�A�A�N�e�B�u

	int number;

	int graphHandle;

	// �ړ�
	void Move();

	// ����
	void Erase();

public:
	Effect_Explosion(float x, float y, int blendDecrease, int particleGH);

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(int scrollX, int scrollY);

	// isActive���擾
	bool GetIsActive();
};