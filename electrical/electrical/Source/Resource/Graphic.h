#pragma once

#include <vector>
#include "../Stage/Stage.h"
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBomb.h"
#include "../Character/Chara_EnemyElectric.h"
#include "../Character/Chara_EnemyWater.h"

class Graphic
{
private:
	std::vector<int> images;
	int mask;								// �}�X�N�摜
	int player[4 * e_P_STATE_NUM];			// �v���C���[
	int enemyBomb[4 * e_EB_STATE_NUM];		// ���e�G�l�~�[
	int enemyElectric[4 * e_EE_STATE_NUM];	// �e�G�l�~�[
	int enemyWater[4 * e_EW_STATE_NUM];		// ���e�G�l�~�[
	int electricGun;						// �d�C�e
	int waterGun;							// ���e
	int particle;							// �p�[�e�B�N��
	int mapChip[e_MAP_NUM];					// �}�b�v�`�b�v
	int background[2];						// �w�i
	int uiPlayer;							// �v���C���[UI
	int uiManipulationMethod[2];			// ������@UI
	int uiHelp[2];							// �w���vUI
	int title;								// �^�C�g��
	int uiTitle[2];							// �^�C�g��UI
	int ending;								// �G���f�B���O
	int uiReady;							// READY_UI
	int frame;								// �g

	int MyLoadGraph(const char *filename);
	int MyLoadDivGraph(const char *fileName, int n,
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

	int GetMask();
	int GetPlayer(int index);
	int GetEnemyBomb(int index);
	int GetEnemyElectric(int index);
	int GetEnemyWater(int index);
	int GetElectricGun();
	int GetWaterGun();
	int GetParticle();
	int GetMapChip(int index);
	int GetBackground(int index);
	int GetUIPlayer();
	int GetUIManipulationMethod(int index);
	int GetUIHelp(int index);
	int GetTitle();
	int GetUITitle(int index);
	int GetEnding();
	int GetUIReady();
	int GetFrame();
};