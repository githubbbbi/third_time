#pragma once

#include "SceneBase.h"

class SceneTitle:public SceneBase
{
private:
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