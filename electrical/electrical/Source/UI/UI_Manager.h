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

	// �X�V����
	void Update(int playerHp, int playerMaxHp,
				int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// �`�揈��
	void Draw(int playerHp, int playerMaxHp,
			  int playerBattery, int playerMaxBattery, bool isDrawUIMM);

	// uiReady->GetIsReady()���擾
	bool GetIsReady();
};