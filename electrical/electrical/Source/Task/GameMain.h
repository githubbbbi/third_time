#pragma once

#include "../Character/CharacterBase.h"
#include "../Character/CharacterPlayer.h"

class GameMain
{
private:
	CharacterBase *player;

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