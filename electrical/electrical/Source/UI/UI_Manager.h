#pragma once

#include "UI_Player.h"
#include "UI_ManipulationMethod.h"

class UI_Manager
{
private:
	UI_Player *uiPlayer;
	UI_ManipulationMethod *uiMainpulation;

public:
	UI_Manager();
	~UI_Manager() = default;

	void Update(int playerHp, int playerMaxHp,
				int playerBattery, int playerMaxBattery, bool isDrawUIMM);
	void Draw(int playerHp, int playerMaxHp,
			  int playerBattery, int playerMaxBattery, bool isDrawUIMM);
};