#include "DxLib.h"
#include "Graphic.h"

Graphic::Graphic()
{
	MyLoadDivGraph("Resource/Graphic/Character/Player/player.png",
				   4 * e_P_STATE_NUM, 4, e_P_STATE_NUM, CHARA_SIZE, CHARA_SIZE, player);
	enemyBomb = MyLoadGraph("Resource/Graphic/Character/Enemy/bomb.png");
	enemyElectric = MyLoadGraph("Resource/Graphic/Character/Enemy/electric.png");
	enemyWater = MyLoadGraph("Resource/Graphic/Character/Enemy/water.png");
	electricGun = MyLoadGraph("Resource/Graphic/Weapon/electricGun.png");
	waterGun = MyLoadGraph("Resource/Graphic/Weapon/waterGun.png");
	particle = MyLoadGraph("Resource/Graphic/Effects/particle.png");
	MyLoadDivGraph("Resource/Graphic/MapChip/mapChip.png",
				   e_MAP_NUM, e_MAP_NUM, 1, CHIP_SIZE, CHIP_SIZE, map);
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

int Graphic::GetPlayer(int index)
{
	return player[index];
}

int Graphic::GetEnemyBomb()
{
	return enemyBomb;
}

int Graphic::GetEnemyElectric()
{
	return enemyElectric;
}

int Graphic::GetEnemyWater()
{
	return enemyWater;
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

int Graphic::GetMap(int index)
{
	return map[index];
}