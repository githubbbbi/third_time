#pragma once

#include "SceneBase.h"

class SceneTitle:public SceneBase
{
private:
	// �������������ɕϐ��錾(�����I�����������Ă�����)


	// ���C�e�B���O�X�V����
	void LightingUpdate();
	
	// ���C�e�B���O�`�揈��
	void LightingDraw();

	// �V�[���J��
	void SceneChange();

	// �Q�[���I��
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};