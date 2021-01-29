#pragma once

#include "SceneBase.h"
#include <vector>
#include "../Effect/Effect_Ligthning.h"
#include "../UI/UI_Title.h"

class SceneTitle:public SceneBase
{
private:
	std::vector<Effect_Lightning *> lightnings;
	UI_Title *ui;

	int x;		// ���S���W
	int y;		// ���S���W
	int width;	// ����
	int height;	// �c��

	// ���C�g�j���O�X�V����
	void UpdateLightning();

	// ���C�g�j���O�`�揈��
	void DrawLightning();

	// �V�[���J��
	void SceneChange(bool isSCPossible);

	// �Q�[���I��
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle();

	void Initialize() override;
	void Update(bool isSCPossible) override;
	void Draw() override;
};