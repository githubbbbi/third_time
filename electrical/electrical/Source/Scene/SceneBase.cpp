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

// シーン遷移するまでの時間
int SceneBase::SceneChangeTime()
{
	// タイトル→ゲームまたはゲーム→ゲーム
	if ( nextScene == e_GAME )
	{
		return 120;
	}

	// ゲーム→エンディング
	if ( nextScene == e_ENDING )
	{
		return 210;
	}

	// エンディング→タイトル
	if ( nextScene == e_TITLE )
	{
		return 0;
	}

	return 0;
}

bool SceneBase::GetIsSceneChange()
{
	static int timer = 0;
	if ( !isSceneChange )
	{
		timer = 0;
		return false;
	}

	// 一定時間経過でTRUEを返す
	if ( timer++ < SceneChangeTime() )
	{
		return false;
	}

	return true;
}

bool SceneBase::GetIsGameEnd()
{
	return isGameEnd;
}