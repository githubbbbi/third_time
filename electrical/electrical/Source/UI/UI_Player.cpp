#include "DxLib.h"
#include "UI_Player.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

UI_Player::UI_Player()
{
	x = 20;
	y = 20;

	r = g = b = 255.0f;
	h = 0.0f;
	s = 0.0f;
	v = 255.0f;
}

// �X�V����
void UI_Player::Update(int hp, int maxHp, int battery, int maxBattery)
{
	// HSV����RGB�֕ϊ�
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);
}

// �`�揈��
void UI_Player::Draw(int hp, int maxHp, int battery, int maxBattery)
{
	// HP & BATTERY�o�[
	for ( int i = 0; i < 100; i++ )
	{
		if ( i <= ((float)hp / maxHp) * 100.0f && hp < 0 )
		{
			DrawLine(82 + (int)(i * 2.6), 25, 114 + (int)(i * 2.6), 57, GetColor(0xF0 - (100 - i), 0x30, 0x30), 2);
		}

		if ( i <= ((float)battery / maxBattery) * 100.0f && battery < 0 )
		{
			DrawLine(110 + (int)(i * 2.4), 66, 90 + (int)(i * 2.4), 86, GetColor(0x30, 0xF0 - (100 - i), 0x30), 2);
		}
	}

	// UI�摜
	DrawGraph(x, y, Graphic::GetInstance()->GetUIPlayer(), true);

	// ����
	DrawFormatString(180, 32, GetColor(255, 255, 255), "%d% / 100", hp);
	DrawFormatString(180, 70, GetColor(255, 255, 255), "%d% / 100", battery);
}