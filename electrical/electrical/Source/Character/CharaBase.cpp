#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"

// �R���X�g���N�^
CharaBase::CharaBase(float x, float y, int radius,
					 float speed, int hp, int attackPower, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->graphHandle = graphHandle;

	this->hp = hp;
	this->attackPower = attackPower;

	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
}

// �L�����N�^�̗���
void CharaBase::CharaFall()
{
	// ����(��ʊO�ł͗������Ȃ�)
	if ( isJump )
	{
		// �������x�𑝂₷
		gravity += GRAVITY;

		// �������x���ړ��ʂɉ�����
		moveY += gravity;
	}
	// �W�����v���łȂ���΃W�����v�����Ȃ�
	else
	{
		gravity = 0.0f;
	}
}

// �L�����N�^�̈ړ�
void CharaBase::CharaMove()
{
	// ����
	CharaFall();

	// �_�~�[ �����X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	float dummy = 0.0f;

	// �L�����N�^�̍���A�E��A�����A�E�㕔���ɓ����蔻�肪����
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă����ꍇ�␳����

	// �㉺�̈ړ��ʂ��`�F�b�N
	// ���� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x - radius, y + radius, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = 0.0f;
	}

	// �E�� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x + radius, y + radius, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = 0.0f;
	}

	// ���� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x - radius, y - radius, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = GRAVITY;
	}

	// �E�� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x + radius, y - radius, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = GRAVITY;
	}

	// �㉺�ړ��ʂ�������
	y += moveY;

	// ���E�̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - radius, y + radius, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + radius, y + radius, &moveX, &dummy);	// �E��
	Utility::MapHitCheck(x - radius, y - radius, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + radius, y - radius, &moveX, &dummy);	// �E��

	// ���E�ړ��ʂ�������
	x += moveX;

	// �ڒn����
	// �L�����N�^�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
	if ( Utility::GetMapParam(x - radius, y + radius + 1.0f) != e_BLOCK &&
		Utility::GetMapParam(x + radius, y + radius + 1.0f) != e_BLOCK )
	{
		// ���ꂪ�Ȃ��ꍇ�A�W�����v���ɂ���
		isJump = true;
	}
	else if ( gravity > 0.0f )
	{
		// ���ꂪ����ꍇ�A�ڒn��
		isJump = false;
	}
}

// �摜�̌�����ω�
void CharaBase::ChangeGraphicDirection()
{
	// ���ɐi�s
	if ( moveX < 0.0f )
	{
		isLeftWard = true;
	}
	// �E�ɐi�U
	else if ( moveX > 0.0f )
	{
		isLeftWard = false;
	}
}

// HP(�o�b�e���[)���Ȃ�
void CharaBase::HpZero()
{
	if ( hp <= 0 )
	{
		isAlive = false;
	}
}

// X���W���擾
float CharaBase::GetPosX()
{
	return x;
}

// Y���W���擾
float CharaBase::GetPosY()
{
	return y;
}

// ���a���擾
int CharaBase::GetRadius()
{
	return radius;
}

// �U���͂��擾
int CharaBase::GetAttackPower()
{
	return attackPower;
}

// isAlive���擾
bool CharaBase::GetIsAlive()
{
	return isAlive;
}

// isLeftWard���擾
bool CharaBase::GetIsLeftWard()
{
	return isLeftWard;
}

// �_���[�W���󂯂�
void CharaBase::ReceiveDamage(int attackPower)
{
	hp -= attackPower;
}