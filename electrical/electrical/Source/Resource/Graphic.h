#pragma once

#include <vector>
#include "../Stage/Stage.h"

class Graphic
{
private:
	static std::vector<int> images;
	static int player;			// �v���C���[
	static int enemyBomb;		// ���e�G�l�~�[
	static int enemyElectric;	// �e�G�l�~�[
	static int enemyWater;		// ���e�G�l�~�[
	static int electricGun;		// �d�C�e
	static int waterGun;		// ���e
	static int particle;		// �p�[�e�B�N��
	static int map[e_MAP_KIND_NUM];

	static int myLoadGraph(const char *filename);
	static int myLoadDivGraph(const char *fileName, int n,
							  int xn, int yn, int w, int h, int *buf);

public:
	Graphic() = default;
	~Graphic() = default;

	static void Load();

	// ���܂Ń��[�h�����摜���������
	static void Release();

	static int GetPlayer();
	static int GetEnemyBomb();
	static int GetEnemyElectric();
	static int GetEnemyWater();
	static int GetElectricGun();
	static int GetWaterGun();
	static int GetParticle();
	static int GetMap(int index);
};