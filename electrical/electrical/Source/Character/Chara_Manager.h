#pragma once

#include <vector>

#include "../Character/Chara_Player.h"
#include "../Character/Chara_EnemyAbsorption.h"
#include "../Character/Weapon/ElectricGun.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<CharaEnemyBase *>enemys;
	std::vector<ElectricGun *> electricGun;

	int playerGH;			// �v���C���[
	int electricGunGH;		// �d�C�e
	int enemyAbsorptionGH;	// �z���G�l�~�[

	float shakeX, shakeY;// �V�F�C�N
	float shakeAddX, shakeAddY;

	// �G�l�~�[�Ǘ�
	void EnemyManager();

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
	void Draw();
};