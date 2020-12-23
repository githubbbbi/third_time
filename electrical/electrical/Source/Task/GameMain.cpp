#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputManager.h"
#include "../Utility/Utility.h"


// �R���X�g���N�^
GameMain::GameMain()
{
	// �L�����N�^�[�C���X�^���X����
	charaManager = new Chara_Manager;

	// �X�e�[�W�C���X�^���X����
	int mapGH[e_MAP_KIND_NUM];
	LoadDivGraph("Resource/Graphic/MapChip/mapChip.png", 
				 e_MAP_KIND_NUM, e_MAP_KIND_NUM, 1, CHIP_SIZE, CHIP_SIZE, mapGH);
	stage = new Stage(mapGH);

	// �w�i
	backgroundGH = LoadGraph("Resource/Graphic/Background/background.png");

	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
}

// �f�X�g���N�^
GameMain::~GameMain()
{
	delete charaManager;
}

// ����������
void GameMain::Initialize()
{
	// �L�����N�^�[
	charaManager->Initialize();

	// �V�F�C�N
	shakeX = 0.0f;
	shakeY = 0.0f;
	shakeAddX = 0.0f;
	shakeAddY = 0.0f;
}

// �X�V����
void GameMain::Update()
{
	// ����
	InputManager::Update();

	// �L�����N�^�[
	charaManager->Update(&shakeAddX, &shakeAddY);

	// �X�e�[�W
	stage->Update();

	// �V�F�C�N
	Utility::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddX);
}

// �`�揈��
void GameMain::Draw()
{
	// �w�i
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX, WIN_HEIGHT / 2 - (int)shakeY,
				  1.0, 0.0, backgroundGH, true);

	// �L�����N�^�[
	charaManager->Draw(shakeX, shakeY);

	// �X�e�[�W
	stage->Draw(shakeX, shakeY);
}

// �I������
void GameMain::Finalize()
{

}