#pragma once

#include "CharacterBase.h"

class CharacterPlayer:public CharacterBase
{
private:
	// �ړ�
	void Move();

public:
	// �R���X�g���N�^�錾
	CharacterPlayer(int x, int y, int speed,
					int radius, int graphHandle);

	// ����������
	void Initialize() override;

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;
};