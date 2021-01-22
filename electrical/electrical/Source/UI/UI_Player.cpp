#include "DxLib.h"
#include "UI_Player.h"
#include "../Utility/Utility.h"
#include "../Resource/Graphic.h"

UI_Player::UI_Player()
{
	line[0] = { 82.0f, 25.0f, 32.0f,
				255.0f, 255.0f, 255.0f,
				0.0f, 230.0f, 230.0f };
	line[1] = { 95.0f, 66.0f, 20.0f,
				255.0f, 255.0f, 255.0f,
				30.0f, 230.0f, 200.0f };

	x = 20;
	y = 20;
}

// �X�V����
void UI_Player::Update(int hp, int maxHp, int battery, int maxBattery)
{
	// hp�̎c�ʂɍ��킹�ĐF��ς��� 50�ȏ�ŗ΁A20�ȏ�ŉ��F�A1�ȏ�Ő�
	ChangeHSV(hp, maxHp);

	// HSV����RGB�֕ϊ�
	for ( int i = 0; i < 2; i++ )
	{
		Utility::ConvertHSVtoRGB(&line[i].r, &line[i].g, &line[i].b,
								 line[i].h, line[i].s, line[i].v);
	}
}

// �`�揈��
void UI_Player::Draw(int hp, int maxHp, int battery, int maxBattery)
{
	// HP�o�[�̕`��
	for ( int i = 0; i < ((float)hp / (float)maxHp) * 100.0f; i++ )
	{
		// hp�̎c�ʂɂ��F��ς���
		if ( ((float)hp / (float)maxHp) * 100.0f > 50 )
		{
			DrawLineAA(line[0].x + i * 2.6f,
					   line[0].y,
					   line[0].x + line[0].size + i * 2.6f,
					   line[0].y + line[0].size,
					   GetColor((int)line[0].r,
								(int)line[0].g - (100 - i), (int)line[0].b), 3);
		}
		else if ( ((float)hp / (float)maxHp) * 100.0f > 20 )
		{
			DrawLineAA(line[0].x + i * 2.6f,
					   line[0].y,
					   line[0].x + line[0].size + i * 2.6f,
					   line[0].y + line[0].size,
					   GetColor((int)line[0].r - (50 - i / 2),
								(int)line[0].g - (50 - i / 2), (int)line[0].b), 3);
		}
		else if ( ((float)hp / (float)maxHp) * 100.0f > 0 )
		{
			DrawLineAA(line[0].x + i * 2.6f,
					   line[0].y,
					   line[0].x + line[0].size + i * 2.6f,
					   line[0].y + line[0].size,
					   GetColor((int)line[0].r - (50 - i),
								(int)line[0].g, (int)line[0].b), 3);
		}
	}

	// BATTERY�o�[�̕`��
	for ( int i = 0; i < ((float)battery / (float)maxBattery) * 100.0f; i++ )
	{
		if ( battery > 0 )
		{
			DrawLineAA(line[1].x + line[1].size + i * 2.3f,
					   line[1].y,
					   line[1].x + i * 2.3f,
					   line[1].y + line[1].size,
					   GetColor((int)line[1].r + i / 2,
								(int)line[1].g + i * 3 / 10, (int)line[1].b), 3);
		}
	}

	// UI�摜
	DrawGraph(x, y, Graphic::GetInstance()->GetUIPlayer(), true);

	// ����
	DrawFormatString(180, 32, GetColor(255, 255, 255), "%d / 100", hp);
	DrawFormatString(180, 70, GetColor(255, 255, 255), "%d / 100", battery);
}

// hp�̎c�ʂɍ��킹�ĐF��ς���
void UI_Player::ChangeHSV(int hp, int maxHp)
{
	// 50�ȏ�ŗ΁A20�ȏ�ŉ��F�A1�ȏ�Ő�
	if ( ((float)hp / (float)maxHp) * 100.0f > 50 )
	{
		line[0].h = 120.0f;
		line[0].s = 230.0f;
		line[0].v = 230.0f;
	}
	else if ( ((float)hp / (float)maxHp) * 100.0f > 20 )
	{
		line[0].h = 60.0f;
		line[0].s = 230.0f;
		line[0].v = 230.0f;
	}
	else
	{
		line[0].h = 0.0f;
		line[0].s = 230.0f;
		line[0].v = 230.0f;
	}
}