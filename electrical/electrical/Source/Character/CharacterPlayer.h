#pragma once

#include "CharacterBase.h"

class CharacterPlayer:public CharacterBase
{
private:
	// 移動
	void Move();

public:
	// コンストラクタ宣言
	CharacterPlayer(int x, int y, int speed,
					int radius, int graphHandle);

	// 初期化処理
	void Initialize() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;
};