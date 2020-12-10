#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"


// �R���X�g���N�^
GameMain::GameMain()
{
	charaManager = nullptr;
}

// �f�X�g���N�^
GameMain::~GameMain()
{
	delete charaManager;
}

// ����������
void GameMain::Initialize()
{
	// �L�����N�^�[�C���X�^���X����
	charaManager = new Chara_Manager;

	// �L�����N�^�[
	charaManager->Initialize();
}

// �X�V����
void GameMain::Update()
{
	// �L�[�{�[�h
	InputKey::Update();

	// �p�b�h
	InputPad::Update();

	// �L�����N�^�[
	charaManager->Update();
}

// �`�揈��
void GameMain::Draw()
{
	// �L�����N�^�[
	charaManager->Draw();
}

// �I������
void GameMain::Finalize()
{

}