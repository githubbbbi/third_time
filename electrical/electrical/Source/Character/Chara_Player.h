#pragma once

#include "CharaBase.h"

class Chara_Player:public CharaBase
{
private:
	// �ړ�
	void Move();

public:
	Chara_Player(int x, int y, int speed,
					int radius, int graphHandle);
	~Chara_Player();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};