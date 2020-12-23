#pragma once

#include <vector>
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBase.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int playerGH;			// �v���C���[
	int electricGunGH;		// �d�C�e
	int enemyBombGH;		// ���e�G�l�~�[
	int enemyGunGH;		// �e�G�l�~�[

	// �G�l�~�[�Ǘ�
	void EnemyManager(float *shakeAddX, float *shakeAddY);

	// �L�����N�^���m�̓����蔻��
	void CharaCollision();

	// �U�������Ǘ�
	void WeaponManager();

	// �U���̓����蔻��
	void AttackCollision();

public:
	Chara_Manager();
	~Chara_Manager();

	// ����������
	void Initialize();

	// �X�V����
	void Update(float *shakeAddX, float *shakeAddY);

	// �`�揈��
	void Draw(float shakeX, float shakeY);
};