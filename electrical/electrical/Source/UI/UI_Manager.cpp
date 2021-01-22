#include "UI_Manager.h"

UI_Manager::UI_Manager()
{
	uiPlayer = new UI_Player;
}

// �X�V����
void UI_Manager::Update(int playerHp, int playerMaxHp,
						int playerBattery, int playerMaxBattery)
{
	uiPlayer->Update(playerHp, playerMaxHp, 
					 playerBattery, playerMaxBattery);
}

// �`�揈��
void UI_Manager::Draw(int playerHp, int playerMaxHp,
					  int playerBattery, int playerMaxBattery)
{
	uiPlayer->Draw(playerHp, playerMaxHp,
					 playerBattery, playerMaxBattery);
}