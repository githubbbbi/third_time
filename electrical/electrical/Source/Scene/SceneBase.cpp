#include "SceneBase.h"

SceneBase::SceneBase()
{
	isSceneChange = false;
	isGameEnd = false;
}

bool SceneBase::GetIsSceneChange()
{
	return isSceneChange;
}

bool SceneBase::GetIsGameEnd()
{
	return isGameEnd;
}