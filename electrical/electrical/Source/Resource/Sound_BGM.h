#pragma once

#include <vector>

enum BGM_Info
{
	e_TITLE_BGM,	// �^�C�g��
	e_GAME_BGM		// �Q�[��
};

class Sound_BGM
{
private:
	std::vector<int> BGM;

	int title;		// �^�C�g��
	int game;		// ���C���Q�[��

	int MyLoadSoundMem(const char *filename);

	// �T�E���h�̉��ʂ�ݒ�
	void MyChangeVolumeSoundMem();

	// �T�E���h�̍Đ����`�F�b�N�A�Đ�
	void CheckAndPlay(int soundHandle);

	// �T�E���h�̍Đ����`�F�b�N�A��~
	void CheckAndStop(int soundHandle);

public:
	Sound_BGM();
	~Sound_BGM() = default;

	static Sound_BGM *GetInstance()
	{
		static Sound_BGM BGM;
		return &BGM;
	}

	// Load()���Ă΂��ƃR���X�g���N�^���Ă΂��
	void Load() {};

	// ���܂Ń��[�h����SE���������
	void Release();

	/**
	 * @brief
	 * BGM���Đ�����
	 * @param BGM_Info bgm �Đ�����BGM
	 */
	void PlayBGM(BGM_Info bgm);

	/**
	 * @brief
	 * BGM���~����
	 * @param BGM_Info bgm ��~����BGM
	 */
	void StopBGM(BGM_Info bgm);
};