#pragma once

class CharaBase
{
protected:
	int x, y;// ���S���W
	int moveX, moveY;// �ړ���
	int speed;// �X�s�[�h
	int radius;// ���a
	int graphHandle;// �摜�n���h��

	bool isAlive;// �����t���O
	bool isLeftWard;// �������t���O

	bool isJump;// �W�����v�t���O

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// �}�b�v�Ƃ̓����蔻��
	void MapCollision();

public:
	// �R���X�g���N�^�錾
	CharaBase(int x, int y, int speed, 
				  int radius, int graphHandle);

	//// ����������
	//virtual void Initialize() = 0;

	//// �X�V����
	//virtual void Update() = 0;

	//// �`�揈��
	//virtual void Draw() = 0;
};