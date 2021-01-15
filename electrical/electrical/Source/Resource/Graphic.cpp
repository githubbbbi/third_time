#include "DxLib.h"
#include "Graphic.h"

std::vector<int> Graphic::images = { 0 };

int Graphic::player = 0;
int Graphic::enemyBomb = 0;
int Graphic::enemyElectric = 0;
int Graphic::enemyWater = 0;
int Graphic::electricGun = 0;
int Graphic::waterGun = 0;
int Graphic::particle = 0;
int Graphic::map[] = { 0 };

void Graphic::Load()
{
	player = myLoadGraph("Resource/Graphic/Character/Player/player.png");
	enemyBomb = myLoadGraph("Resource/Graphic/Character/Enemy/bomb.png");
	enemyElectric = myLoadGraph("Resource/Graphic/Character/Enemy/electric.png");
	enemyWater = myLoadGraph("Resource/Graphic/Character/Enemy/water.png");
	electricGun = myLoadGraph("Resource/Graphic/Weapon/electricGun.png");
	waterGun = myLoadGraph("Resource/Graphic/Weapon/waterGun.png");
	particle = myLoadGraph("Resource/Graphic/Effects/particle.png");
	myLoadDivGraph("Resource/Graphic/MapChip/mapChip.png",
				 e_MAP_KIND_NUM, e_MAP_KIND_NUM, 1, CHIP_SIZE, CHIP_SIZE, map);
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

int Graphic::myLoadGraph(const char *filename)
{
	int temp = LoadGraph(filename);
	images.push_back(temp);

	return temp;
}

int Graphic::myLoadDivGraph(const char *fileName, int n,
							int xn, int yn, int w, int h, int *buf)
{
	int temp = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	for ( int i = 0; i < n; i++ )
	{
		images.push_back(buf[i]);
	}

	return temp;
}

int Graphic::GetPlayer()
{
	return player;
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