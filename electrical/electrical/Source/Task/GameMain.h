#pragma once

#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"

class GameMain
{
private:
	Chara_Manager *charaManager;
	Stage *stage;
	EffectManager *effects;

	int backgroundGH;			// �w�i�摜
	int scrollX, scrollY;		// �X�N���[����

	// �G�t�F�N�g�Ǘ�
	// �uLocal�v��EffectManager�N���X�Ɩ��O�����Ȃ��悤
	void LocalEffectManager();

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