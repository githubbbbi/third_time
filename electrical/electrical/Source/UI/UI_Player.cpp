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
				120.0f, 230.0f, 230.0f };

	x = 20;
	y = 20;
}

// 更新処理
void UI_Player::Update(int hp, int maxHp, int battery, int maxBattery)
{
	// HSVからRGBへ変換
	for ( int i = 0; i < 2; i++ )
	{
		Utility::ConvertHSVtoRGB(&line[i].r, &line[i].g, &line[i].b,
								 line[i].h, line[i].s, line[i].v);
	}
}

// 描画処理
void UI_Player::Draw(int hp, int maxHp, int battery, int maxBattery)
{
	// HP & BATTERYバー
	for ( int i = 0; i < 100; i++ )
	{
		if ( i <= ((float)hp / (float)maxHp) * 100.0f && hp > 0 )
		{
			// HPバーの描画
			DrawLineAA(line[0].x + i * 2.6f,
					   line[0].y,
					   line[0].x + line[0].size + i * 2.6f,
					   line[0].y + line[0].size,
					   GetColor((int)line[0].r - (100 - i),
								(int)line[0].g, (int)line[0].b), 3);
		}

		if ( i <= ((float)battery / (float)maxBattery) * 100.0f && battery > 0 )
		{

			// BATTERYバーの描画
			DrawLineAA(line[1].x + line[1].size + i * 2.3f,
					   line[1].y,
					   line[1].x + i * 2.3f,
					   line[1].y + line[1].size,
					   GetColor((int)line[1].r ,
								(int)line[1].g - (100 - i), (int)line[1].b), 3);
		}
	}

	// UI画像
	DrawGraph(x, y, Graphic::GetInstance()->GetUIPlayer(), true);

	// 数字
	DrawFormatString(180, 32, GetColor(255, 255, 255), "%d% / 100", hp);
	DrawFormatString(180, 70, GetColor(255, 255, 255), "%d% / 100", battery);
}