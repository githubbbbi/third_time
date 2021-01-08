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

	// �G�t�F�N�g
	int particleGH = LoadGraph("Resource/Graphic/Effects/particle.png");
	effects = new EffectManager(particleGH);

	scrollX = 0;
	scrollY = 0;
}

// �f�X�g���N�^
GameMain::~GameMain()
{
	delete charaManager;
	delete stage;
	delete effects;
}

// ����������
void GameMain::Initialize()
{
	// �L�����N�^�[
	charaManager->Initialize();
}

// �X�V����
void GameMain::Update()
{
	// ����
	InputManager::Update();

	// �G�t�F�N�g
	effects->Update();

	// �X�N���[��
	Utility::Scroll((int)charaManager->GetScrollCenterX(),
					(int)charaManager->GetScrollCenterY(), &scrollX, &scrollY);

	// �X�e�[�W
	stage->Update();

	// �L�����N�^�[
	charaManager->Update();
}

// �`�揈��
void GameMain::Draw()
{
	// �w�i
	DrawRotaGraph(WIN_WIDTH / 2 - (int)effects->GetShakeX() - scrollX,
				  WIN_HEIGHT / 2 - (int)effects->GetShakeY() - scrollY,
				  1.0, 0.0, backgroundGH, true);

	// �X�e�[�W
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(), scrollX, scrollY);

	// �L�����N�^�[
	charaManager->Draw(effects->GetShakeX(),
					   effects->GetShakeY(), scrollX, scrollY);

	// �G�t�F�N�g
	effects->Draw();
}

// �I������
void GameMain::Finalize()
{

}