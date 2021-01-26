#pragma once

#include "SceneBase.h"
#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"
#include "../UI/UI_Manager.h"

class SceneGame:public SceneBase
{
private:
	Chara_Manager *characters;
	Stage *stage;
	EffectManager *effects;
	UI_Manager *ui;

	int scrollX, scrollY;	// �X�N���[����
	int screenX, screenY;	// �X�N���[�����S���W
	bool isScroll;			// �X�N���[���t���O

	// �X�N���[�����W�����߂�
	void Screen();

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