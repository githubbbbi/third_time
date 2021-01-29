#include "DxLib.h"
#include "Mask.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

const double EX_RATE_UP_SPEED = 1.0;
const double EX_RATE_DOWN_SPEED = 1.5;
const double MAX_EX_RATE = 75.0;
const double MIN_EX_RATE = 0.0;

// �ϐ�������
int Mask::screenHandle = -1;
double Mask::exRate = 0.0;

// �}�X�N�̃Z�b�g
void Mask::SetMask()
{
	// �A���t�@�`�����l���t���̕`��ΏۃO���t�B�b�N�n���h�����쐬
	screenHandle = MakeScreen(WIN_WIDTH, WIN_HEIGHT, TRUE);

	// �}�X�N�摜�̃T�C�Y��ݒ�
	exRate = MIN_EX_RATE;

	// �}�X�N�@�\�̏��������s��
	CreateMaskScreen();

	// MakeScreen�ō쐬�����O���t�B�b�N�n���h�����Z�b�g
	SetMaskScreenGraph(screenHandle);
}

// �}�X�N�̊g��
bool Mask::MaskScaleUp()
{
	if ( exRate < MAX_EX_RATE )
	{
		exRate += EX_RATE_UP_SPEED;
	}
	else if ( exRate >= MAX_EX_RATE )
	{
		exRate = MAX_EX_RATE;
		return true;
	}

	return false;
}

// �}�X�N�̏k��
bool Mask::MaskScaleDown()
{
	static int timer = 0;

	if ( exRate > MIN_EX_RATE )
	{
		exRate -= EX_RATE_DOWN_SPEED;
	}
	else if ( exRate <= MIN_EX_RATE )
	{
		exRate = MIN_EX_RATE;

		// ��莞�Ԍo�߂�true
		if ( timer++ > 30 )
		{
			timer = 0;
			return true;
		}
	}

	return false;
}

// �}�X�N�̕`��
void Mask::DrawMask()
{
	// �`�����}�X�N�p�̉摜�ɕύX
	SetDrawScreen(screenHandle);

	// �}�X�N�p�̉摜���N���A
	ClearDrawScreen();

	// �}�X�N�摜�`��
	DrawRotaGraph(WIN_WIDTH / 2, WIN_HEIGHT / 2,
				  exRate, 0.0, Graphic::GetInstance()->GetMask(), true);

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// ����ʂ��N���A
	ClearDrawScreen();
}

// �}�X�N�̌㏈��
void Mask::LoopMask()
{
	// �}�X�N��L���ɂ���
	SetUseMaskScreenFlag(TRUE);

	// ��ʂ����ς��Ɏl�p�`��`��
	DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);

	// �}�X�N�𖳌��ɂ���
	SetUseMaskScreenFlag(FALSE);
}

// �g�嗦���ő�̔���
bool Mask::IsExRateMax()
{
	return exRate >= MAX_EX_RATE;
}

// �g�嗦���ő�̔���
bool Mask::IsExRateMin()
{
	return exRate <= MIN_EX_RATE;
}