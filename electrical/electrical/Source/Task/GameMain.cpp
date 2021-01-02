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
	scrollX = 0;
	scrollY = 0;
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

	// �V�F�C�N
	Utility::Shake(&shakeX, &shakeY, &shakeAddX, &shakeAddX);

	// �X�N���[��
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// �X�e�[�W
	stage->Update();

	// �L�����N�^�[
	charaManager->Update(&shakeAddX, &shakeAddY);
}

// �`�揈��
void GameMain::Draw()
{
	// �w�i
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX - scrollX, WIN_HEIGHT / 2 - (int)shakeY - scrollY,
				  1.0, 0.0, backgroundGH, true);

	// �X�e�[�W
	stage->Draw(shakeX, shakeY, scrollX, scrollY);

	// �L�����N�^�[
	charaManager->Draw(shakeX, shakeY, scrollX, scrollY);
}

// �I������
void GameMain::Finalize()
{

}