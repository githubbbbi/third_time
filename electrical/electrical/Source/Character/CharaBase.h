#pragma once

class CharaBase
{
protected:
	int x, y;// ���S���W
	int moveX, moveY;// �ړ���
	int speed;// �X�s�[�h
	int radius;// ���a
	int graphHandle;// �摜�n���h��

	int hp;// HP

	bool isAlive;// �����t���O
	bool isLeftWard;// �������t���O

	bool isJump;// �W�����v�t���O

	// �摜�̌�����ω�
	void ChangeGraphicDirection();

	// �}�b�v�Ƃ̓����蔻��
	void MapCollision();

public:
	// �R���X�g���N�^�錾
	CharaBase(int x, int y, int radius,
			  int speed, int hp, int graphHandle);

	// X���W���擾
	int GetPosX();

	// Y���W���擾
	int GetPosY();

	// ���a���擾
	int GetRadius();

	//// ����������
	//virtual void Initialize() = 0;

	//// �X�V����
	//virtual void Update() = 0;

	//// �`�揈��
	//virtual void Draw() = 0;
};