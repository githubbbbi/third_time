#pragma once

#include "UI_Player.h"
#include "UI_ManipulationMethod.h"
#include "UI_Ready.h"

class UI_Manager
{
private:
	UI_Player *uiPlayer;
	UI_ManipulationMethod *uiMainpulation;
	UI_Ready *uiReady;

public:
	UI_Manager();
	~UI_Manager();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(int playerHp, int playerMaxHp,
				int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// 描画処理
	void Draw(int playerHp, int playerMaxHp,
			  int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// uiReady->GetIsReady()を取得
	bool GetIsReady();
};