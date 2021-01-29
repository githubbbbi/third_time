#pragma once

#include "SceneBase.h"

class SceneEnding:public SceneBase
{
private:
	int x;	// ���S���W
	int y;	// ���S���W

	// �V�[���J��
	void SceneChange(bool isSCPossible);

	// �Q�[���I��
	void GameEnd();

public:
	SceneEnding();
	~SceneEnding() = default;

	void Initialize() override;
	void Update(bool isSCPossible) override;
	void Draw() override;
};