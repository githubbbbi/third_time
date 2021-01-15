#pragma once

#include <vector>
#include "../Stage/Stage.h"

class Graphic
{
private:
	std::vector<int> images;
	int player[4 + 2];			// �v���C���[
	int enemyBomb;				// ���e�G�l�~�[
	int enemyElectric;			// �e�G�l�~�[
	int enemyWater;				// ���e�G�l�~�[
	int electricGun;			// �d�C�e
	int waterGun;				// ���e
	int particle;				// �p�[�e�B�N��
	int map[e_MAP_KIND_NUM];	// �}�b�v

	int myLoadGraph(const char *filename);
	int myLoadDivGraph(const char *fileName, int n,
							  int xn, int yn, int w, int h, int *buf);

public:
	Graphic();
	~Graphic() = default;

	static Graphic *GetInstance()
	{
		static Graphic graphic;
		return &graphic;
	}

	// Load()���Ă΂��ƃR���X�g���N�^���Ă΂��
	void Load() {};

	// ���܂Ń��[�h�����摜���������
	void Release();

	int GetPlayer(int index);
	int GetEnemyBomb();
	int GetEnemyElectric();
	int GetEnemyWater();
	int GetElectricGun();
	int GetWaterGun();
	int GetParticle();
	int GetMap(int index);
};