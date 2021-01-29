#pragma once

class UI_Ready
{
private:
	int x;			// 中心座標
	int y;			// 中心座標
	bool isReady;	// READYフラグ

public:
	UI_Ready();
	~UI_Ready() = default;

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// isReadyを取得
	bool GetIsReady();
};