#pragma once

class GameMain
{
private:


public:
	// コンストラクタ
	GameMain();

	// デストラクタ
	~GameMain();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 終了処理
	void Finalize();
};