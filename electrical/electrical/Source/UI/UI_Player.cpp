#include "DxLib.h"
#include "UI_Player.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

UI_Player::UI_Player()
{
	line[0] = { 82.0f, 25.0f, 32.0f };
	line[1] = { 95.0f, 66.0f, 20.0f };

	x = 20;
	y = 20;

	r = g = b = 255.0f;
	h = 0.0f;
	s = 230.0f;
	v = 230.0f;
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
		if (i <= ((float)hp / (float)maxHp) * 100.0f && hp > 0)
		{
			// HP�o�[�̕`��
			DrawLineAA(line[0].x + i * 2.6f,
						line[0].y,
						line[0].x + line[0].size + i * 2.6f,
						line[0].y + line[0].size,
						GetColor((int)r - (100 - i), (int)g, (int)b), 3);
		}

		if (i <= ((float)battery / (float)maxBattery) * 100.0f && battery > 0)
		{

			// BATTERY�o�[�̕`��
			// r��g�����ւ��āA�V�����ϐ�����炸�ɐF��ς��Ă���
			DrawLineAA(line[1].x + line[1].size + i * 2.3f,
						line[1].y,
						line[1].x + i * 2.3f,
						line[1].y + line[1].size,
						GetColor((int)g, (int)r - (100 - i), (int)b), 3);
		}
	}

	// UI�摜
	DrawGraph(x, y, Graphic::GetInstance()->GetUIPlayer(), true);

	// ����
	DrawFormatString(180, 32, GetColor(255, 255, 255), "%d% / 100", hp);
	DrawFormatString(180, 70, GetColor(255, 255, 255), "%d% / 100", battery);
}