#pragma once

#include "../Task/GameMain.h"

class System
{
private:
	GameMain *gameMain;

public:
	// �R���X�g���N�^
	System();

	// �f�X�g���N�^
	~System();

	// ���C������
	bool Main();

	// ����������
	bool Initialize();

	// ���C�����[�v
	bool MainLoop();

	// �I������
	void Finalize();
};