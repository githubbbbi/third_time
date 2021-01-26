#pragma once

class Effect_Lightning
{
private:
	// ��
	int posX;
	int posY;
	int posX2;
	int posY2;
	int oldPosX;
	int oldPosY;
	int oldPosX2;
	int oldPosY2;

	// ����
	int valX;
	int valY;

	// ���˕ǂ̍��W
	int wallX;
	int wallY;
	int wallX2;
	int wallY2;

	int timer;

public:
	Effect_Lightning(int wallX,int wallY,int wallX2,int wallY2);
	~Effect_Lightning() = default;

	// �򋗗�
	bool IsLengthOver();

	// �X�V����
	void Update();

	// �ړ�
	void Move();

	// ����
	void LightningCollision();

	// �`�揈��
	void Draw();
};