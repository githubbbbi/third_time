#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

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

	oldX = x;
	oldY = y;

	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	isAlive = true;
	isLeftWard = false;

	isJump = false;
	isFall = false;
}

// �L�����N�^�̃W�����v
void CharaBase::CharaJump()
{
	if ( !isJump && !isFall )
	{
		gravity = JUMP_POWER;
		isJump = true;
	}
}

// �L�����N�^�̗���
void CharaBase::CharaFall()
{
	// ����
	if ( isJump || isFall )
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
void CharaBase::CharaMove(float hitWidth, float hitHeight)
{
	// 1�t���[���O�̍��W�擾
	oldX = x;
	oldY = y;

	// ����
	CharaFall();

	// �_�~�[ �����X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	float dummy = 0.0f;

	// �L�����N�^�̍���A�E��A�����A�E�㕔���ɓ����蔻�肪����
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă����ꍇ�␳����

	// �㉺�̈ړ��ʂ��`�F�b�N
	// ���� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x - hitWidth, y + hitHeight, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// �E�� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x + hitWidth, y + hitHeight, &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// ���� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x - hitWidth, y - hitHeight, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// �E�� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x + hitWidth, y - hitHeight, &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// �㉺�ړ��ʂ�������
	y += moveY;

	// ���E�̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - hitWidth, y + hitHeight, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitWidth, y + hitHeight, &moveX, &dummy);	// �E��
	Utility::MapHitCheck(x - hitWidth, y - hitHeight, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitWidth, y - hitHeight, &moveX, &dummy);	// �E��

	// ���E�ړ��ʂ�������
	x += moveX;

	// �ڒn����
	// �L�����N�^�̍����܂��͉E�����n�ʂł��邩���ׂ�
	if ( Stage::GetMapParam(x - hitWidth, y + hitHeight + 1.0f) == e_MAP_BLOCK ||
		Stage::GetMapParam(x + hitWidth, y + hitHeight + 1.0f) == e_MAP_BLOCK )
	{
		// ���ꂪ����ꍇ�A�ڒn��
		isFall = false;
		isJump = false;
	}
	else
	{
		// ���ꂪ�Ȃ��ꍇ�A�������ɂ���
		isFall = true;
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

// HP�Ǘ�
void CharaBase::HpManager()
{
	HpZero();
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

// oldX���W���擾
float CharaBase::GetPosOldX()
{
	return oldX;
}

// oldY���W���擾
float CharaBase::GetPosOldY()
{
	return oldY;
}

float CharaBase::GetSpeed()
{
	return speed;
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

// �G�ƓG�łȂ��ꍇ�̃L�����N�^���m���ڐG
void CharaBase::CharactersCollision()
{
	x -= moveX;
}