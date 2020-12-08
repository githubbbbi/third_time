#include "DxLib.h"
#include "GameMain.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"


// �R���X�g���N�^
GameMain::GameMain()
{
	
}

// �f�X�g���N�^
GameMain::~GameMain()
{
	delete player;
}

// ����������
void GameMain::Initialize()
{
	// �v���C���[����
	int playerGH = LoadGraph("Resource/Graphic/player.png");
	player = new CharacterPlayer(WIN_WIDTH / 2, WIN_HEIGHT / 2, 5,
								 32, playerGH);
}

// �X�V����
void GameMain::Update()
{
	// �L�[�{�[�h
	InputKey::KeyUpdate();

	// �p�b�h
	InputPad::PadUpdate();

	// �v���C���[
	player->Update();
}

// �`�揈��
void GameMain::Draw()
{
	// �v���C���[
	player->Draw();
}

// �I������
void GameMain::Finalize()
{

}