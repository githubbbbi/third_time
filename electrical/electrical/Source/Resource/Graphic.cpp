#include "DxLib.h"
#include "Graphic.h"
#include "../Define/Define.h"
#include "../Background/Background.h"

Graphic::Graphic()
{
	// ì«Ç›çûÇ›
	mask = MyLoadGraph("Resource/Graphic/Mask/mask.png");
	MyLoadDivGraph("Resource/Graphic/Character/Player/player.png",
				   4 * e_P_STATE_NUM, 4, e_P_STATE_NUM, CHARA_SIZE, CHARA_SIZE, player);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/bomb.png",
				   4 * e_EB_STATE_NUM, 4, e_EB_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyBomb);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/electric.png",
				   4 * e_EE_STATE_NUM, 4, e_EE_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyElectric);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/water.png",
				   4 * e_EW_STATE_NUM, 4, e_EW_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyWater);
	electricGun = MyLoadGraph("Resource/Graphic/Weapon/electric_gun.png");
	waterGun = MyLoadGraph("Resource/Graphic/Weapon/water_gun.png");
	particle = MyLoadGraph("Resource/Graphic/Effects/particle.png");
	MyLoadDivGraph("Resource/Graphic/MapChip/map_chip.png",
				   e_MAP_NUM, e_MAP_NUM, 1, CHIP_SIZE, CHIP_SIZE, mapChip);
	MyLoadDivGraph("Resource/Graphic/Background/background.png",
				   2, 1, 2, BG_GRAPH_SIZE_X, BG_GRAPH_SIZE_Y, background);
	uiPlayer = MyLoadGraph("Resource/Graphic/UI/UI_player.png");
	MyLoadDivGraph("Resource/Graphic/UI/UI_manipulation_method.png",
				   2, 2, 1, 144, 208, uiManipulationMethod);
	MyLoadDivGraph("Resource/Graphic/UI/UI_help.png",
				   2, 1, 2, 96, 32, uiHelp);
	title = MyLoadGraph("Resource/Graphic/Title/title.png");
	MyLoadDivGraph("Resource/Graphic/UI/UI_title.png",
				   2, 1, 2, 140, 24, uiTitle);
	ending = MyLoadGraph("Resource/Graphic/Ending/ending.png");
	uiReady = MyLoadGraph("Resource/Graphic/UI/UI_ready.png");
}

// ç°Ç‹Ç≈ÉçÅ[ÉhÇµÇΩâÊëúÇâï˙Ç∑ÇÈ
void Graphic::Release()
{
	for ( unsigned i = 0; i < images.size(); i++ )
	{
		DeleteGraph(images[i]);
	}

	images.clear();
}

int Graphic::MyLoadGraph(const char *filename)
{
	int temp = LoadGraph(filename);
	images.push_back(temp);

	return temp;
}

int Graphic::MyLoadDivGraph(const char *fileName, int n,
							int xn, int yn, int w, int h, int *buf)
{
	int temp = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	for ( int i = 0; i < n; i++ )
	{
		images.push_back(buf[i]);
	}

	return temp;
}

int Graphic::GetMask()
{
	return mask;
}

int Graphic::GetPlayer(int index)
{
	return player[index];
}

int Graphic::GetEnemyBomb(int index)
{
	return enemyBomb[index];
}

int Graphic::GetEnemyElectric(int index)
{
	return enemyElectric[index];
}

int Graphic::GetEnemyWater(int index)
{
	return enemyWater[index];
}

int Graphic::GetElectricGun()
{
	return electricGun;
}

int Graphic::GetWaterGun()
{
	return waterGun;
}

int Graphic::GetParticle()
{
	return particle;
}

int Graphic::GetMapChip(int index)
{
	return mapChip[index];
}

int Graphic::GetBackground(int index)
{
	return background[index];
}

int Graphic::GetUIPlayer()
{
	return uiPlayer;
}

int Graphic::GetUIManipulationMethod(int index)
{
	return uiManipulationMethod[index];
}

int Graphic::GetUIHelp(int index)
{
	return uiHelp[index];
}

int Graphic::GetTitle()
{
	return title;
}

int Graphic::GetUITitle(int index)
{
	return uiTitle[index];
}

int Graphic::GetEnding()
{
	return ending;
}

int Graphic::GetUIReady()
{
	return uiReady;
}