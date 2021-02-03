#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBase.h"
#include "../Define/Define.h"

enum CharaSpawnInfo
{
	e_CharaPlayer,				// �v���C���[
	e_CharaEnemyBomb,			// �{����
	e_CharaEnemyElectric,		// �d�C�e�G�l�~�[
	e_CharaEnemyWater,			// ���e�G�l�~�[
	e_CharaPlayer_ChecKPoint	// �v���C���[�`�F�b�N�|�C���g
};

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int spawnData[MAP_COUNT_Y][MAP_COUNT_X];		// �X�|�[���f�[�^
	bool isEnemySpawn[MAP_COUNT_Y][MAP_COUNT_X];	// �G�l�~�[�X�|�[���t���O
	bool isPassCheckPoint;							// �`�F�b�N�|�C���g�ʉ߃t���O

	int displaceX;			// �X�N���[���̒��S�ɕ`�悷�邽�߂ɂ��炷��
	int displaceY;			// �X�N���[���̒��S�ɕ`�悷�邽�߂ɂ��炷��

	float explosionX;								// �����̒��S�ƂȂ���W
	float explosionY;								// �����̒��S�ƂȂ���W

	// �t�@�C���ǂݍ���
	bool LoadFile();

	// �v���C���[�̃X�|�[��
	void PlayerSpawn();

	// �G�l�~�[�̐���
	void EnemyGenerate(int screenX, int screenY);

	// �G�l�~�[�Ǘ�
	void EnemyManager(int screenX, int screenY);

	// �L�����N�^���m�̓����蔻��
	void CharaCollision();

	// �U���̓����蔻��
	void AttackCollision();

	// �`�F�b�N�|�C���g�̒ʉߔ���
	void PassCheckPoint();

public:
	Chara_Manager();
	~Chara_Manager();

	// ����������
	bool Initialize();

	// �X�V����
	void Update(int screenX, int screenY);

	// �`�揈��
	void Draw(float shakeX, float shakeY,
			  int scrollX, int scrollY);

	// displaceX��ݒ�
	void SetDisplaceX(int displaceX);

	// displaceY��ݒ�
	void SetDisplaceY(int displaceY);

	// �X�N���[���̒��S���W���擾
	float GetScrollCenterX();
	float GetScrollCenterY();

	// �����̒��S�ƂȂ�X���W���擾
	float GetExplosionPosX();

	// �����̒��S�ƂȂ�Y���W���擾
	float GetExplosionPosY();

	// �L�����N�^�[�̎��S���擾
	bool GetIsCharaDeath();

	// �v���C���[�̒��SX���W���擾
	float GetPlayerX();

	// �v���C���[�̒��SY���W���擾
	float GetPlayerY();

	// �v���C���[��HP���擾
	int GetPlayerHp();

	// �v���C���[�̍ő�HP���擾
	int GetPlayerMaxHp();

	// �v���C���[�̍ő�o�b�e���[���擾
	int GetPlayerBattery();

	// �v���C���[�̃o�b�e���[���擾
	int GetPlayerMaxBattery();

	// �v���C���[isAlive���擾
	bool GetPlayerIsAlive();

	// �v���C���[�̃S�[���t���O���擾
	bool GetPlayerIsGoal();
};