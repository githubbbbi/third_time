#pragma once

class UI_ManipulationMethod
{
private:
	typedef struct
	{
		int x;			// 中心座標
		int y;			// 中心座標
		int graphIndex;	// グラフインデックス
	}UI;

	UI ui[2];

public:
	UI_ManipulationMethod();
	~UI_ManipulationMethod() = default;

	// 更新処理
	void Update(bool isDrawUIMM);

	// 描画処理
	void Draw(bool isDrawUIMM);
};