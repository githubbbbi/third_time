#pragma once

#include "../Scene/SceneManager.h"

class System
{
private:
	SceneManager *scene;

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