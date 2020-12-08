#pragma once

#include "../Character/CharacterBase.h"
#include "../Character/CharacterPlayer.h"

class GameMain
{
private:
	CharacterBase *player;

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