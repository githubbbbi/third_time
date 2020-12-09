#include "DxLib.h"
#include "Chara_Player.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(int x, int y, int speed,
								 int radius, int graphHandle):
	CharaBase(x, y, speed, radius, graphHandle)
{
}

Chara_Player::~Chara_Player()
{

}

// ����������
void Chara_Player::Initialize()
{
	moveX = 0;
	moveY = 0;
}

// �ړ�
void Chara_Player::Move()
{
	// �ړ��ʏ�����
	moveX = 0;
	moveY = 0;

	// ���ړ�
	if ( InputKey::IsKeyInputNow(KEY_INPUT_LEFT) ||
		InputPad::IsPadInputNow(PAD_INPUT_LEFT) )
	{
		moveX -= speed;
	}

	//�E�ړ�
	if ( InputKey::IsKeyInputNow(KEY_INPUT_RIGHT) ||
		InputPad::IsPadInputNow(PAD_INPUT_RIGHT) )
	{
		moveX += speed;
	}

	// �W�����v
	if ( InputKey::IsKeyInputNow(KEY_INPUT_UP) ||
		InputPad::IsPadInputNow(PAD_INPUT_A) )
	{
		isJump = true;
	}

	// �ړ��ʉ��Z
	x += moveX;
	y += moveY;

	// ��ʓ��ɂƂǂ܂�(X�����ɂ��Ă̂�)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// �X�V����
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		ChangeGraphicDirection();
	}
}

// �`�揈��
void Chara_Player::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}