#pragma once

enum Scene
{
	e_NONE,
	e_TITLE,		// �^�C�g��
	e_GAME,			// �Q�[��
	e_ENDING,		// �G���f�B���O
};

class SceneBase
{
protected:
	Scene nextScene;	// ���̃V�[��
	bool isSceneChange;	// �V�[���J�ڃt���O
	bool isGameEnd;		// �Q�[���I���t���O

private:
	// �V�[���J�ڂ���܂ł̎���
	int SceneChangeTime();

public:
	SceneBase();
	virtual ~SceneBase() = default;

	virtual void Initialize() = 0;
	virtual void Update(bool isSCPossible) = 0;
	virtual void Draw() = 0;

	Scene GetNextScene();
	bool GetIsSceneChange();
	bool GetIsGameEnd();
};