#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBase.h"
#include "../Define/Define.h"

enum EnemysInfo
{
	e_EnemyBomb,		// �{����
	e_EnemyElectric,	// �d�C�e�G�l�~�[
	e_EnemyWater,		// ���e�G�l�~�[
	e_EnemyNum
};

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int spawnData[MAP_COUNT_Y][MAP_COUNT_X];		// �X�|�[���f�[�^
	bool isEnemySpawn[MAP_COUNT_Y][MAP_COUNT_X];	// �G�l�~�[�X�|�[���t���O

	float explosionX;								// �����̒��S�ƂȂ���W
	float explosionY;								// �����̒��S�ƂȂ���W

	// �t�@�C���ǂݍ���
	bool LoadFile();

	// �G�l�~�[�̐���
	void EnemyGenerate(int screenX, int screenY);

	// �G�l�~�[�Ǘ�
	void EnemyManager(int screenX, int screenY);

	// �L�����N�^���m�̓����蔻��
	void CharaCollision();

	// �U���̓����蔻��
	void AttackCollision();

public:
	Chara_Manager();
	~Chara_Manager();

	// ����������
	bool Initialize();

	// �X�V����
	void Update(int screenX, int screenY);

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �X�N���[���̒��S���W���擾
	float GetScrollCenterX();
	float GetScrollCenterY();

	// �����̒��S�ƂȂ�X���W���擾
	float GetExplosionPosX();

	// �����̒��S�ƂȂ�Y���W���擾
	float GetExplosionPosY();

	// �L�����N�^�[�̎��S���擾
	bool GetIsCharaDeath();

	// HP���擾
	int GetPlayerHp();

	// �ő�HP���擾
	int GetPlayerMaxHp();

	// �ő�o�b�e���[���擾
	int GetPlayerBattery();

	// �o�b�e���[���擾
	int GetPlayerMaxBattery();
};