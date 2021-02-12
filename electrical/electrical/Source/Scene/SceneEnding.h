#pragma once

#include "SceneBase.h"

// �G���f�B���O�摜�T�C�Y
extern const int ED_GRAPH_SIZE_X;
extern const int ED_GRAPH_SIZE_Y;

class SceneEnding:public SceneBase
{
private:
	int x;			// ���S���W
	int y;			// ���S���W
	double exRate;	// �g�嗦

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