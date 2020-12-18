#include "DxLib.h"
#include "Mask.h"
#include "../Define/Define.h"

// �ϐ�������
int Mask::graphHandle = -1;
int Mask::screenHandle = -1;

double Mask::sizeRate = 0.0;

// �}�X�N�̃Z�b�g
void Mask::SetMask()
{
	// �}�X�N�摜
	graphHandle = LoadGraph("Resource/Graphic/Mask/mask.png");

	// �A���t�@�`�����l���t���̕`��ΏۃO���t�B�b�N�n���h�����쐬
	screenHandle = MakeScreen(WIN_WIDTH, WIN_HEIGHT, TRUE);

	// �}�X�N�摜�̃T�C�Y��ݒ�
	sizeRate = 50.0;

	// �}�X�N�@�\�̏��������s��
	CreateMaskScreen();

	// MakeScreen�ō쐬�����O���t�B�b�N�n���h�����Z�b�g
	SetMaskScreenGraph(screenHandle);
}

// �}�X�N�̎��k
void Mask::MaskShrink()
{
	if ( sizeRate > 0.0 )
	{
		//sizeRate -= 0.5;
	}
}

// �}�X�N�̕`��
void Mask::DrawMask()
{
	// �}�X�N�̎��k
	MaskShrink();

	// �`�����}�X�N�p�̉摜�ɕύX
	SetDrawScreen(screenHandle);

	// �}�X�N�p�̉摜���N���A
	ClearDrawScreen();

	// �}�X�N�摜�`��
	DrawRotaGraph(WIN_WIDTH / 2, WIN_HEIGHT / 2,
				  sizeRate, 0.0, graphHandle, true);

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