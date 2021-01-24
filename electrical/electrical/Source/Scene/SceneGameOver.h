#pragma once

#include "SceneBase.h"

class SceneGameOver:public SceneBase
{
private:
	// �V�[���J��
	void SceneChange();

	// �Q�[���I��
	void GameEnd();

public:
	SceneGameOver();
	~SceneGameOver() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
};