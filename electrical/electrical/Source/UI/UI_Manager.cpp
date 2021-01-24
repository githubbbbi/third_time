#include "UI_Manager.h"

UI_Manager::UI_Manager()
{
	uiPlayer = new UI_Player;
	uiMainpulation = new UI_ManipulationMethod;
}

// 更新処理
void UI_Manager::Update(int playerHp, int playerMaxHp,
						int playerBattery, int playerMaxBattery)
{
	uiPlayer->Update(playerHp, playerMaxHp, 
					 playerBattery, playerMaxBattery);
}

// 描画処理
void UI_Manager::Draw(int playerHp, int playerMaxHp,
					  int playerBattery, int playerMaxBattery)
{
	// プレイヤー
	uiPlayer->Draw(playerHp, playerMaxHp,
					 playerBattery, playerMaxBattery);

	// 操作方法
	uiMainpulation->Draw();
}