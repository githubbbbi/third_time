#pragma once

#include <iostream>
#include "SceneBase.h"

class SceneManager
{
private:
	std::unique_ptr<SceneBase> nowScene;	// ���ݏ������s���Ă���V�[��
	Scene scene;							// ���݂̃V�[��

	// �t�F�[�h�C��
	bool FadeIn();

	// �t�F�[�h�A�E�g
	bool FadeOut();

	// �V�[���J��
	void SceneChange();

public:
	SceneManager();
	~SceneManager() = default;

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	// �Q�[���I��
	bool GetIsGameEnd();
};