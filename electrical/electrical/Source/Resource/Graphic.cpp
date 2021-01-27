#include "DxLib.h"
#include "Graphic.h"

Graphic::Graphic()
{
	mask = MyLoadGraph("Resource/Graphic/Mask/mask.png");
	MyLoadDivGraph("Resource/Graphic/Character/Player/player.png",
				   4 * e_P_STATE_NUM, 4, e_P_STATE_NUM, CHARA_SIZE, CHARA_SIZE, player);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/bomb.png",
				   4 * e_EB_STATE_NUM, 4, e_EB_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyBomb);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/electric.png",
				   4 * e_EE_STATE_NUM, 4, e_EE_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyElectric);
	MyLoadDivGraph("Resource/Graphic/Character/Enemy/water.png",
				   4 * e_EW_STATE_NUM, 4, e_EW_STATE_NUM, CHARA_SIZE, CHARA_SIZE, enemyWater);
	electricGun = MyLoadGraph("Resource/Graphic/Weapon/electricGun.png");
	waterGun = MyLoadGraph("Resource/Graphic/Weapon/waterGun.png");
	particle = MyLoadGraph("Resource/Graphic/Effects/particle.png");
	MyLoadDivGraph("Resource/Graphic/MapChip/map_chip.png",
				   e_MAP_NUM, e_MAP_NUM, 1, CHIP_SIZE, CHIP_SIZE, mapChip);
	background = MyLoadGraph("Resource/Graphic/Background/background.png");
	uiPlayer = MyLoadGraph("Resource/Graphic/UI/UI_player.png");
	uiManipulationMethod = MyLoadGraph("Resource/Graphic/UI/UI_manipulation_method.png");
	title = MyLoadGraph("Resource/Graphic/Title/title.png");
	uiTitle = MyLoadGraph("Resource/Graphic/UI/UI_title.png");
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

int Graphic::GetBackground()
{
	return background;
}

int Graphic::GetUIPlayer()
{
	return uiPlayer;
}

int Graphic::GetUIManipulationMethod()
{
	return uiManipulationMethod;
}

int Graphic::GetTitle()
{
	return title;
}

int Graphic::GetUITitle()
{
	return uiTitle;
}