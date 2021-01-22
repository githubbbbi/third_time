#pragma once

#include "UI_Player.h"

class UI_Manager
{
private:
	UI_Player *uiPlayer;

public:
	UI_Manager();
	~UI_Manager() = default;

	void Update(int playerHp, int playerMaxHp, 
				int playerBattery, int playerMaxBattery);
	void Draw(int playerHp, int playerMaxHp,
			  int playerBattery, int playerMaxBattery);
};