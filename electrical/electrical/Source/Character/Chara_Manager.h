#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBase.h"

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	float explosionX;		// �����̒��S�ƂȂ���W
	float explosionY;		// �����̒��S�ƂȂ���W

	// �G�l�~�[�̐���
	void EnemySpawn(int screenX, int screenY);

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
	void Initialize();

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
};