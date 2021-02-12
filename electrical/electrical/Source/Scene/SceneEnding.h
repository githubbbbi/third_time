#pragma once

#include "SceneBase.h"

// エンディング画像サイズ
extern const int ED_GRAPH_SIZE_X;
extern const int ED_GRAPH_SIZE_Y;

class SceneEnding:public SceneBase
{
private:
	int x;			// 中心座標
	int y;			// 中心座標
	double exRate;	// 拡大率

	// シーン遷移
	void SceneChange(bool isSCPossible);

	// ゲーム終了
	void GameEnd();

public:
	SceneEnding();
	~SceneEnding() = default;

	void Initialize() override;
	void Update(bool isSCPossible) override;
	void Draw() override;
};