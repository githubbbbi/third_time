#include "DxLib.h"
#include "UI_ManipulationMethod.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"
#include "../Input/InputManager.h"

UI_ManipulationMethod::UI_ManipulationMethod()
{
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	graphIndex = 0;
}

// �X�V����
void UI_ManipulationMethod::Update(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		return;
	}

	// ���͂��L�[�{�[�h�̏ꍇ
	if ( InputManager::GetIsInputKey() )
	{
		graphIndex = 0;
	}
	// �p�b�h�̏ꍇ
	else if ( InputManager::GetIsInputPad() )
	{
		graphIndex = 1;
	}
}

// �`�揈��
void UI_ManipulationMethod::Draw(bool isDrawUIMM)
{
	if ( !isDrawUIMM )
	{
		return;
	}

	DrawRotaGraph(x, y, 1.5, 0.0,
				  Graphic::GetInstance()->GetUIManipulationMethod(graphIndex), true);
}