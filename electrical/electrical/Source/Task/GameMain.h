#pragma once

#include "../Character/Chara_Manager.h"

class GameMain
{
private:
	Chara_Manager *charaManager;

public:
	// �R���X�g���N�^
	GameMain();

	// �f�X�g���N�^
	~GameMain();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// �I������
	void Finalize();
};