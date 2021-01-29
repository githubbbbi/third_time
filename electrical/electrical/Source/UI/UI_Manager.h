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

	// XVˆ—
	void Update(int playerHp, int playerMaxHp,
				int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// •`‰æˆ—
	void Draw(int playerHp, int playerMaxHp,
			  int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// uiReady->GetIsReady()‚ğæ“¾
	bool GetIsReady();
};