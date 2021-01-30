#include "UI_Manager.h"

UI_Manager::UI_Manager()
{
	uiPlayer = new UI_Player;
	uiMainpulation = new UI_ManipulationMethod;
	uiReady = new UI_Ready;
}

UI_Manager::~UI_Manager()
{
	delete uiPlayer;
	delete uiMainpulation;
	delete uiReady;
}

// ����������
void UI_Manager::Initialize()
{
	// READY
	uiReady->Initialize();
}

// �X�V����
void UI_Manager::Update(int playerHp, int playerMaxHp,
						int playerBattery, int playerMaxBattery, bool isDrawUIMM)
{
	// READY
	uiReady->Update();

	// �v���C���[
	uiPlayer->Update(playerHp, playerMaxHp,
					 playerBattery, playerMaxBattery);

	// ������@
	uiMainpulation->Update(isDrawUIMM);
}

// �`�揈��
void UI_Manager::Draw(int playerHp, int playerMaxHp,
					  int playerBattery, int playerMaxBattery, bool isDrawUIMM)
{
	// �v���C���[
	uiPlayer->Draw(playerHp, playerMaxHp,
				   playerBattery, playerMaxBattery);

	// READY
	uiReady->Draw();

	// READY�\������return
	if ( GetIsReady() )
	{
		return;
	}

	// ������@
	uiMainpulation->Draw(isDrawUIMM);
}

// uiReady->GetIsReady()���擾
bool UI_Manager::GetIsReady()
{
	return uiReady->GetIsReady();
}