#include "DxLib.h"
#include <math.h>
#include "CharaBase.h"
#include "../Utility/Utility.h"
#include "../Define/Define.h"
#include "../Stage/Stage.h"
#include "../Resource/Sound_SE.h"

const int CHARA_SIZE = 56;
const float GRAVITY = 0.850f;
const int INVICIBLE_TIME = 60;

// �R���X�g���N�^
CharaBase::CharaBase(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower)
{
	anim = new CharaAnimation;

	// �ϐ��̏�����
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->radius = radius;
	this->width = width;
	this->height = height;

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

	isAttack = false;

	r = g = b = 255.0f;
	h = 0.0f;
	s = 0.0f;
	v = 255.0f;

	state = 0;
	graphIndex = 0;

	cBlinkingTimer = 0;
	cBlinkingCounter = 0;
	isCBlinking = false;

	bBlinkingTimer = 0;
	bBlinkingCounter = 0;
	isBBlinking = false;

	isKnockBack = false;
	isAttackLeftWard = false;

	invicibleTimer = 0;
	isInvicible = false;

	isExplosion = false;

	blendMode = DX_BLENDMODE_NOBLEND;
	blendValue = 0;
}

// �f�X�g���N�^
CharaBase::~CharaBase()
{
	delete anim;
}

// ����������
void CharaBase::MyInitialize()
{
	oldX = x;
	oldY = y;

	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	isJump = false;
	isFall = false;

	isAttack = false;

	r = g = b = 255.0f;
	h = 0.0f;
	s = 0.0f;
	v = 255.0f;

	state = 0;
	graphIndex = 0;

	cBlinkingTimer = 0;
	cBlinkingCounter = 0;
	isCBlinking = false;

	bBlinkingTimer = 0;
	bBlinkingCounter = 0;
	isBBlinking = false;

	isKnockBack = false;
	isAttackLeftWard = false;

	invicibleTimer = 0;
	isInvicible = false;

	isExplosion = false;

	blendMode = DX_BLENDMODE_NOBLEND;
	blendValue = 0;

	isAlive = true;
}

// �L�����N�^�̃W�����v
void CharaBase::CharaJump(float jumpPower)
{
	if ( !isJump && !isFall )
	{
		gravity = jumpPower;
		isJump = true;
	}
}

// �L�����N�^�̏㏸&����
void CharaBase::CharaRiseAndFall()
{
	// �㏸&����
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
void CharaBase::CharaMove(float hitHalfWidth, float hitHalfHeight)
{
	// 1�t���[���O�̍��W�擾
	oldX = x;
	oldY = y;

	// �㏸&����
	CharaRiseAndFall();

	// X�܂���Y�����̈ړ��ʂɂ��čl�����Ȃ��ꍇ�ɗp����
	float dummy = 0.0f;

	// �L�����N�^�̍���A�E��A�����A�E�㕔���ɓ����蔻�肪����
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă����ꍇ�␳����

	// �㉺�̈ړ��ʂ��`�F�b�N
	// ���� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x - hitHalfWidth, y + hitHalfHeight,
							  &dummy, &moveY) == e_HIT_BLOCK_TOP )
	{
		gravity = 0.0f;
	}

	// �E�� �u���b�N�̏�ӂɒ��n�����ꍇ�A������~
	if ( Utility::MapHitCheck(x + hitHalfWidth, y + hitHalfHeight,
							  &dummy, &moveY) == e_HIT_BLOCK_TOP )
	{
		gravity = 0.0f;
	}

	// ���� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x - hitHalfWidth, y - hitHalfHeight,
							  &dummy, &moveY) == e_HIT_BLOCK_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// �E�� �u���b�N�̉��ӂɏՓ˂����ꍇ�A����
	if ( Utility::MapHitCheck(x + hitHalfWidth, y - hitHalfHeight,
							  &dummy, &moveY) == e_HIT_BLOCK_BOTTOM )
	{
		gravity = GRAVITY;
	}

	// �㉺�ړ��ʂ�������
	y += moveY;

	// ���E�̈ړ��ʂ��`�F�b�N
	Utility::MapHitCheck(x - hitHalfWidth, y + hitHalfHeight, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitHalfWidth, y + hitHalfHeight, &moveX, &dummy);	// �E��
	Utility::MapHitCheck(x - hitHalfWidth, y - hitHalfHeight, &moveX, &dummy);	// ����
	Utility::MapHitCheck(x + hitHalfWidth, y - hitHalfHeight, &moveX, &dummy);	// �E��

	// ���E�ړ��ʂ�������
	x += moveX;

	// �ڒn����
	// �L�����N�^�̍����܂��͉E�����n�ʂł��邩���ׂ�
	if ( (Stage::GetMapParam(x - hitHalfWidth,
							 y + hitHalfHeight + 1.0f) == e_MAP_BLOCK ||
		  Stage::GetMapParam(x + hitHalfWidth,
							 y + hitHalfHeight + 1.0f) == e_MAP_BLOCK) )
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

		// SE�Đ�
		Sound_SE::GetInstance()->PlaySE(e_DEATH_SE, false);
		isAlive = false;
	}
}

// HP�Ǘ�
void CharaBase::HpManager()
{
	HpZero();
}

// �F�_��
void CharaBase::ColorBlinking(float h, float s, float v, int change, int  num)
{
	if ( isCBlinking )
	{
		// �_�ŏI��
		if ( cBlinkingCounter > num )
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

// Blend�ɂ��Ďw�肳�ꂽ�񐔂����_��
void CharaBase::BlendBlinking(int blendMode1, int blendMode2,
							  int blendValue1, int blendValue2, int change, int num)
{
	if ( isBBlinking )
	{
		// �_�ŏI��
		if ( bBlinkingCounter > num )
		{
			this->blendMode = DX_BLENDMODE_NOBLEND;
			this->blendValue = 0;
			bBlinkingCounter = 0;
			bBlinkingTimer = 0;
			isBBlinking = false;

			return;
		}

		// �_��
		bBlinkingTimer++;
		if ( bBlinkingTimer < change )
		{
			this->blendMode = blendMode1;
			this->blendValue = blendValue1;
		}
		else if ( bBlinkingTimer < change * 2 )
		{
			this->blendMode = blendMode2;
			this->blendValue = blendValue2;
		}
		else if ( bBlinkingTimer < change * 3 )
		{
			bBlinkingCounter++;
			bBlinkingTimer = 0;
		}
	}
}

// �m�b�N�o�b�N
void CharaBase::KnockBack()
{
	if ( isKnockBack )
	{
		if ( isCBlinking )
		{
			// ������
			moveX = 0.0f;
			moveY = 0.0f;

			float knockBackSpeed = 0.20f;

			if ( isAttackLeftWard )
			{
				knockBackSpeed *= -1.0f;
			}
			else
			{
				knockBackSpeed *= 1.0f;
			}

			moveX += knockBackSpeed;
		}
		// �F�_�ŏI���Ńm�b�N�o�b�N�I��
		else
		{
			isKnockBack = false;
		}
	}
}

// ���G���̏���
void CharaBase::Invicible()
{
	// �F�_�ł��I��莟�斳�G���Ԃ̃J�E���g�J�n
	if ( isCBlinking || !isInvicible )
	{
		return;
	}

	BlendBlinking(DX_BLENDMODE_ALPHA, DX_BLENDMODE_ALPHA, 150, 200, 4, 5);

	invicibleTimer++;
	if ( invicibleTimer > INVICIBLE_TIME )
	{
		invicibleTimer = 0;
		isInvicible = false;
	}
}

// �A�j���[�V����
void CharaBase::Animation(const int MOTION[][4],
							   const float NORMAL_SPEED, const float DASH_SPEED)
{
	const int num = 4;
	int wait = 10;

	// �ړ���
	if ( moveX != 0.0f || moveY != 0.0f )
	{
		if ( fabsf(speed) == NORMAL_SPEED )
		{
			wait = 10;
		}
		else if ( fabsf(speed) == DASH_SPEED )
		{
			wait = 6;
		}
	}

	int *p = (int *)MOTION;
	graphIndex = anim->AnimationLoop(p, state, wait, num);
}

// �_���[�W���󂯂�
void CharaBase::ReceiveDamage(int attackPower, bool isLeftWard)
{
	hp -= attackPower;

	// SE�Đ�
	Sound_SE::GetInstance()->PlaySE(e_RECEIVE_DAMAGE_SE, false);

	// �F�_�Ńt���OTRUE
	if ( !isCBlinking )
	{
		isCBlinking = true;
	}

	// �u�����h�_�Ńt���OTRUE
	if ( !isBBlinking )
	{
		isBBlinking = true;
	}

	// �m�b�N�o�b�N�t���OTRUE
	if ( !isKnockBack )
	{
		isAttackLeftWard = isLeftWard;
		isKnockBack = true;
	}

	// ���G�t���OTRUE
	if ( !isInvicible )
	{
		isInvicible = true;
	}
}

// ����
void CharaBase::Explosion()
{
	isExplosion = true;
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

// isInvicible���擾
bool CharaBase::GetIsInvicible()
{
	return isInvicible;
}

// isExplosion���擾
bool CharaBase::GetIsExplosion()
{
	return isExplosion;
}