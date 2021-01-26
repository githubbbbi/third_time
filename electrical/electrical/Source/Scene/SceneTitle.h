#pragma once

#include "SceneBase.h"
#include <vector>
#include "../Effect/Effect_Ligthning.h"

class SceneTitle:public SceneBase
{
private:
	std::vector<Effect_Lightning *> lightnings;

	// ���C�g�j���O�X�V����
	void LightningUpdate();

	// ���C�g�j���O�`�揈��
	void LightningDraw();

	// �V�[���J��
	void SceneChange();

	// �Q�[���I��
	void GameEnd();

public:
	SceneTitle();
	~SceneTitle();

	void Initialize() override;
	void Update() override;
	void Draw() override;
};