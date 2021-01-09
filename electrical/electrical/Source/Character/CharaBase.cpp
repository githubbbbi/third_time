#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"

// �R���X�g���N�^
CharaBase::CharaBase(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower, int graphHandle)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->width = width;
	this->height = height;
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

	r = g = b = 255.0f;
	h = 0.0f;
	s = 0.0f;
	v = 255.0f;

	cBlinkingTimer = 0;
	cBlinkingCounter = 0;
	isCBlinking = false;
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
	// �W�����v���ł��������ł��Ȃ���΃W�����v�����Ȃ�
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

	// X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	float dummy = 0.0f;

	// �L�����N�^�̍���A�E��A�����A�E�㕔���ɓ����蔻�肪����
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă����ꍇ�␳����

	// �㉺�̈ړ��ʂ��`�F�b�N
	// ���� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x - hitWidth, y + hitHeight,
							  &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// �E�� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x + hitWidth, y + hitHeight,
							  &dummy, &moveY) == e_HIT_TOP )
	{
		gravity = 0.0f;
	}

	// ���� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x - hitWidth, y - hitHeight,
							  &dummy, &moveY) == e_HIT_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// �E�� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x + hitWidth, y - hitHeight,
							  &dummy, &moveY) == e_HIT_BOTTOM )
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
	if ( Stage::GetMapParam(x - hitWidth, 
							y + hitHeight + 1.0f) == e_MAP_BLOCK ||
		Stage::GetMapParam(x + hitWidth, 
						   y + hitHeight + 1.0f) == e_MAP_BLOCK )
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
		hp = 0;
		isAlive = false;
	}
}

// HP�Ǘ�
void CharaBase::HpManager()
{
	HpZero();
}

// �F�_��
void CharaBase::ColorBlinking(float h, float s, float v, int  noOfTimes)
{
	const int change = 5;

	if ( isCBlinking )
	{
		// �_�ŏI��
		if ( cBlinkingCounter > noOfTimes )
		{
			this->s = 0.0f;
			cBlinkingCounter = 0;
			cBlinkingTimer = 0;
			isCBlinking = false;

			return;
		}

		// �_��
		cBlinkingTimer++;
		if ( cBlinkingTimer < change )
		{
			this->h = h;
			this->s = s;
			this->v = v;
		}
		else if ( cBlinkingTimer < change * 2 )
		{
			this->s = 0.0f;
			this->v = 255.0f;
		}
		else if ( cBlinkingTimer < change * 3 )
		{
			cBlinkingCounter++;
			cBlinkingTimer = 0;
		}
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

// width���擾
int CharaBase::GetWidth()
{
	return width;
}

// height���擾
int CharaBase::GetHeight()
{
	return height;
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
	// �F�_�Ńt���OTRUE
	if ( !isCBlinking )
	{
		isCBlinking = true;
	}

	hp -= attackPower;
}

// �G�ƓG�łȂ��ꍇ�̃L�����N�^���m���ڐG
void CharaBase::CharactersCollision()
{
	moveX = 0.0f;
}