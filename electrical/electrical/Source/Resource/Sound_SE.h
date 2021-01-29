#pragma once

#include <vector>

enum SE_Info
{
	e_GAME_START_SE,			// �Q�[���X�^�[�g
	e_PLAYER_JUMP_SE,			// �v���C���[�̃W�����v
	e_PLAYER_CHAGING_SE,		// �[�d��
	e_SHOT_ELECTRIC_GUN_SE,		// �d�C�e������
	e_SHOT_WATER_GUN_SE,		// ���e������
	e_RECEIVE_DAMAGE_SE,		// �_���[�W���󂯂�
	e_DEATH_SE,					// ���S
	e_OPEN_HELP_SE,				// �w���v���J��
	e_SCROLL_SE,				// �X�N���[��
	e_STAGE_CLEAR_SE			// �X�e�[�W�N���A
};

class Sound_SE
{
private:
	std::vector<int> SE;

	int gameStart;			// �Q�[���X�^�[�g
	int playerJump;			// �v���C���[�̃W�����v
	int playerCharging;		// �[�d��
	int shotElectricGun;	// �d�C�e������
	int shotWaterGun;		// ���e������
	int receiveDamage;		// �_���[�W���󂯂�
	int death;				// ���S
	int openHelp;			// �w���v���J��
	int scroll;				// �X�N���[��
	int stageClear;			// �X�e�[�W�N���A

	int MyLoadSoundMem(const char *filename);

	// �T�E���h�̉��ʂ�ݒ�
	void MyChangeVolumeSoundMem();

	// �T�E���h�̍Đ����`�F�b�N�A�Đ�
	void CheckAndPlay(int soundHandle, bool isCheckSound);

	// �T�E���h�̍Đ����`�F�b�N�A��~
	void CheckAndStop(int soundHandle);

public:
	Sound_SE();
	~Sound_SE() = default;

	static Sound_SE *GetInstance()
	{
		static Sound_SE SE;
		return &SE;
	}

	// Load()���Ă΂��ƃR���X�g���N�^���Ă΂��
	void Load()
	{
	};

	// ���܂Ń��[�h����SE���������
	void Release();

	/**
	 * @brief
	 * SE���Đ�����
	 * @param SE_Info se �Đ�����SE
	 * @param isCheckSound �T�E���h���Đ�����Ă��邩�`�F�b�N����
	 */
	void PlaySE(SE_Info se, bool isCheckSound);

	/**
	 * @brief
	 * SE���~����
	 * @param SE_Info se ��~����SE
	 */
	void StopSE(SE_Info se);

	// ���ׂĂ�SE���~����
	void StopAllSE();
};