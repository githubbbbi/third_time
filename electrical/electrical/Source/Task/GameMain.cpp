#include "DxLib.h"
#include "GameMain.h"
#include "../Input/InputKey.h"


// �R���X�g���N�^
GameMain::GameMain()
{

}

// �f�X�g���N�^
GameMain::~GameMain()
{

}

// ����������
void GameMain::Initialize()
{

}

// �X�V����
void GameMain::Update()
{
	// �L�[�{�[�h
	InputKey::KeyUpdate();


}

// �`�揈��
void GameMain::Draw()
{
	DrawString(500, 300, "�Q�[�����", GetColor(255, 255, 255));
}

// �I������
void GameMain::Finalize()
{

}