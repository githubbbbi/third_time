#pragma once

// タイトル専用のUIクラス
class UI_Title
{
private:
	int x;				// 中心座標
	int y;				// 中心座標
	int trasparency;	// 透過度
	int graphIndex;		// グラフインデックス

public:
	UI_Title();
	~UI_Title() = default;

	// 更新処理
	void Update(bool isBlinking, bool isFlashing);

	// 描画処理
	void Draw();
};