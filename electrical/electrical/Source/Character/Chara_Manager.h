#pragma once

#include <vector>
#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyBomb.h"
#include "../Character/Chara_EnemyGun.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBomb *>enemyBomb;
	std::vector<Chara_EnemyGun *>enemyGun;

	int playerGH;			// �v���C���[
	int electricGunGH;		// �d�C�e
	int enemyBombGH;		// ���e�G�l�~�[
	int enemyGunGH;			// �e�G�l�~�[

	// �G�l�~�[�Ǘ�
	void EnemyManager();

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
	void Update();

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// �X�N���[���̒��S���W���擾
	float GetScrollCenterX();
	float GetScrollCenterY();

	// �G�l�~�[�̎��S
	bool IsEnemyDeath();
};