#include "DxLib.h"
#include "Background.h"
#include "../Define/Define.h"
#include "../Resource/Graphic.h"

// �`�揈��
void Background::Draw(float shakeX, float shakeY)
{
	DrawRotaGraph(WIN_WIDTH / 2 - (int)shakeX, WIN_HEIGHT / 2 - (int)shakeY,
				  1.0, 0.0, Graphic::GetInstance()->GetBackground(), true);
}