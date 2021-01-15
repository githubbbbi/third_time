#pragma once

#include <iostream>
#include "SceneBase.h"

class SceneManager
{
private:
	// ���݂̃V�[��
	std::unique_ptr<SceneBase> nowScene;
	Scene scene;

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