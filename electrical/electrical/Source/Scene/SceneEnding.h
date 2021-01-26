#pragma once

#include "SceneBase.h"

class SceneEnding:public SceneBase
{
private:
	// �V�[���J��
	void SceneChange();

	// �Q�[���I��
	void GameEnd();

public:
	SceneEnding();
	~SceneEnding() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};