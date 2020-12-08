#include "DxLib.h"
#include "CharacterPlayer.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

CharacterPlayer::CharacterPlayer(int x, int y, int speed,
								 int radius, int graphHandle):
	CharacterBase(x, y, speed, radius, graphHandle)
{
}

// ����������
void CharacterPlayer::Initialize()
{

}

// �ړ�
void CharacterPlayer::Move()
{
	// �ړ��ʏ�����
	moveX = 0;
	moveY = 0;

	// ���ړ�
	if ( InputKey::IsKeyInputNow(KEY_INPUT_LEFT) ||
		InputPad::IsPadInputNow(PAD_INPUT_LEFT) )
	{
		isLeftWard = true;
		moveX -= speed;
	}

	//�E�ړ�
	if ( InputKey::IsKeyInputNow(KEY_INPUT_RIGHT) ||
		InputPad::IsPadInputNow(PAD_INPUT_RIGHT) )
	{
		isLeftWard = false;
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
void CharacterPlayer::Update()
{
	if ( isAlive )
	{
		Move();
	}
}

// �`�揈��
void CharacterPlayer::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph(x, y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}