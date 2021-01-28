#include "DxLib.h"
#include "UI_ManipulationMethod.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"
#include "../Input/InputManager.h"

UI_ManipulationMethod::UI_ManipulationMethod()
{
	ui[0] = { 100, WIN_HEIGHT - 25, 0 };
	ui[1] = { WIN_WIDTH / 2, WIN_HEIGHT / 2, 0 };
}

// �X�V����
void UI_ManipulationMethod::Update(bool isDrawUIMM)
{
	// ����ꗗ�`��t���O
	if ( !isDrawUIMM )
	{
		// �w���v
		// ���͂��L�[�{�[�h�̏ꍇ
		if ( InputManager::GetIsInputKey() )
		{
			ui[0].graphIndex = 0;
		}
		// �p�b�h�̏ꍇ
		else if ( InputManager::GetIsInputPad() )
		{
			ui[0].graphIndex = 1;
		}

		return;
	}

	// ����ꗗ
	// ���͂��L�[�{�[�h�̏ꍇ
	if ( InputManager::GetIsInputKey() )
	{
		ui[1].graphIndex = 0;
	}
	// �p�b�h�̏ꍇ
	else if ( InputManager::GetIsInputPad() )
	{
		ui[1].graphIndex = 1;
	}
}

// �`�揈��
void UI_ManipulationMethod::Draw(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		// �w���v
		DrawRotaGraph(ui[0].x, ui[0].y, 1.0, 0.0,
					  Graphic::GetInstance()->GetUIHelp(ui[0].graphIndex), true);

		return;
	}

	// ����ꗗ
	DrawRotaGraph(ui[1].x, ui[1].y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUIManipulationMethod(ui[1].graphIndex), true);
}