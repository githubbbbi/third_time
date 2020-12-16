#pragma once

#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"

class GameMain
{
private:
	Chara_Manager *charaManager;
	Stage *stage;

	int backgroundGH;	// �w�i

	float shakeX, shakeY;// �V�F�C�N
	float shakeAddX, shakeAddY;// �V�F�C�N��

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