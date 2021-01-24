#include "SceneBase.h"

SceneBase::SceneBase()
{
	nextScene = e_NONE;
	isSceneChange = false;
	isGameEnd = false;
}

Scene SceneBase::GetNextScene()
{
	return nextScene;
}

bool SceneBase::GetIsSceneChange()
{
	return isSceneChange;
}

bool SceneBase::GetIsGameEnd()
{
	return isGameEnd;
}