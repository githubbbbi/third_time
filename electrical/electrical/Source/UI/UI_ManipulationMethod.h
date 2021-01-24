#pragma once

class UI_ManipulationMethod
{
private:
	int x;	// 中心座標
	int y;	// 中心座標

public:
	UI_ManipulationMethod();
	~UI_ManipulationMethod() = default;

	// 描画処理
	void Draw();
};