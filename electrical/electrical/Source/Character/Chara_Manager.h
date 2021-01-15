#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBomb.h"
#include "Chara_EnemyElectric.h"
#include "Chara_EnemyWater.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBomb *>enemyBomb;
	std::vector<Chara_EnemyElectric *>enemyElectric;
	std::vector<Chara_EnemyWater *>enemyWater;

	float explosionX;		// �����̒��S�ƂȂ���W
	float explosionY;		// �����̒��S�ƂȂ���W

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

	// �����̒��S�ƂȂ�X���W���擾
	float GetExplosionPosX();

	// �����̒��S�ƂȂ�Y���W���擾
	float GetExplosionPosY();

	// �G�l�~�[�̎��S���擾
	bool GetIsEnemyDeath();
};