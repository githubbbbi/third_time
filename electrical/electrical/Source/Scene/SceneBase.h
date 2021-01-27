#pragma once

enum Scene
{
	e_NONE,
	e_TITLE,		// �^�C�g��
	e_GAME,			// �Q�[��
	e_GAMEOVER,		// �Q�[���I�[�o�[
	e_ENDING,		// �G���f�B���O
};

class SceneBase
{
protected:
	Scene nextScene;	// ���̃V�[��
	bool isSceneChange;	// �V�[���J�ڃt���O
	bool isGameEnd;		// �Q�[���I���t���O

public:
	SceneBase();
	virtual ~SceneBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Scene GetNextScene();
	bool GetIsSceneChange();
	bool GetIsGameEnd();
};