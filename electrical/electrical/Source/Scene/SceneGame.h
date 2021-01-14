#pragma once

#include "SceneBase.h"
#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"

class SceneGame:public SceneBase
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

	// �V�[���J��
	void SceneChange();

	// �Q�[���I��
	void GameEnd();

public:
	// �R���X�g���N�^
	SceneGame();

	// �f�X�g���N�^
	~SceneGame();

	// ����������
	void Initialize() override;

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;

	// �I������
	void Finalize();
};