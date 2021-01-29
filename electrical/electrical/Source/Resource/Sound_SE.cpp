#include "DxLib.h"
#include "Sound_SE.h"

Sound_SE::Sound_SE()
{
	// �ǂݍ���
	gameStart = MyLoadSoundMem("Resource/Sound/SE/game_start.mp3");
	playerJump = MyLoadSoundMem("Resource/Sound/SE/player_jump.wav");
	playerCharging = MyLoadSoundMem("Resource/Sound/SE/player_charging.mp3");
	shotElectricGun = MyLoadSoundMem("Resource/Sound/SE/shot_electric_gun.mp3");
	shotWaterGun = MyLoadSoundMem("Resource/Sound/SE/shot_water_gun.mp3");
	receiveDamage = MyLoadSoundMem("Resource/Sound/SE/receive_damage.mp3");
	death = MyLoadSoundMem("Resource/Sound/SE/death.mp3");
	openHelp = MyLoadSoundMem("Resource/Sound/SE/open_help.mp3");
	scroll = MyLoadSoundMem("Resource/Sound/SE/scroll.mp3");
	stageClear = MyLoadSoundMem("Resource/Sound/SE/stage_clear.mp3");

	// �T�E���h�̉��ʂ�ݒ�
	MyChangeVolumeSoundMem();
}

// �T�E���h�̉��ʂ�ݒ�
void Sound_SE::MyChangeVolumeSoundMem()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		ChangeVolumeSoundMem((int)(255.0f * 60.0f / 100.0f), SE[i]);
	}

	ChangeVolumeSoundMem((int)(255.0f * 70.0f / 100.0f), gameStart);
	ChangeVolumeSoundMem((int)(255.0f * 40.0f / 100.0f), playerJump);
	ChangeVolumeSoundMem((int)(255.0f * 35.0f / 100.0f), shotElectricGun);
	ChangeVolumeSoundMem((int)(255.0f * 65.0f / 100.0f), shotWaterGun);
	ChangeVolumeSoundMem((int)(255.0f * 90.0f / 100.0f), receiveDamage);
}

// ���܂Ń��[�h����SE���������
void Sound_SE::Release()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		DeleteGraph(SE[i]);
	}

	SE.clear();
}

int Sound_SE::MyLoadSoundMem(const char *filename)
{
	int temp = LoadSoundMem(filename);
	SE.push_back(temp);

	return temp;
}

// �T�E���h�̍Đ����`�F�b�N�A�Đ�
void Sound_SE::CheckAndPlay(int soundHandle, bool isCheckSound)
{
	if ( isCheckSound &&
		CheckSoundMem(soundHandle) )
	{
		return;
	}

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

// �T�E���h�̍Đ����`�F�b�N�A��~
void Sound_SE::CheckAndStop(int soundHandle)
{
	if ( !CheckSoundMem(soundHandle) )
	{
		return;
	}

	StopSoundMem(soundHandle);
}

// SE�Đ�
void Sound_SE::PlaySE(SE_Info se, bool isCheckSound)
{
	switch ( se )
	{
		case e_GAME_START_SE:
			// �Q�[���X�^�[�g
			CheckAndPlay(gameStart, isCheckSound);
			break;

		case e_PLAYER_JUMP_SE:
			// �v���C���[�̃W�����v
			CheckAndPlay(playerJump, isCheckSound);
			break;

		case e_PLAYER_CHAGING_SE:
			// �[�d��
			CheckAndPlay(playerCharging, isCheckSound);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// �d�C�e������
			CheckAndPlay(shotElectricGun, isCheckSound);
			break;

		case e_SHOT_WATER_GUN_SE:
			// ���e������
			CheckAndPlay(shotWaterGun, isCheckSound);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// �_���[�W���󂯂�
			CheckAndPlay(receiveDamage, isCheckSound);
			break;

		case e_DEATH_SE:
			// ���S
			CheckAndPlay(death, isCheckSound);
			break;

		case e_OPEN_HELP_SE:
			// �w���v���J��
			CheckAndPlay(openHelp, isCheckSound);
			break;

		case e_SCROLL_SE:
			// �X�N���[��
			CheckAndPlay(scroll, isCheckSound);
			break;

		case e_STAGE_CLEAR_SE:
			// �X�e�[�W�N���A
			CheckAndPlay(stageClear, isCheckSound);
			break;

		default:
			break;
	}
}

// SE��~
void Sound_SE::StopSE(SE_Info se)
{
	switch ( se )
	{
		case e_GAME_START_SE:
			// �Q�[���X�^�[�g
			CheckAndStop(gameStart);
			break;

		case e_PLAYER_JUMP_SE:
			// �v���C���[�̃W�����v
			CheckAndStop(playerJump);
			break;

		case e_PLAYER_CHAGING_SE:
			// �[�d��
			CheckAndStop(playerCharging);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// �d�C�e������
			CheckAndStop(shotElectricGun);
			break;

		case e_SHOT_WATER_GUN_SE:
			// ���e������
			CheckAndStop(shotWaterGun);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// �_���[�W���󂯂�
			CheckAndStop(receiveDamage);
			break;

		case e_DEATH_SE:
			// ���S
			CheckAndStop(death);
			break;

		case e_OPEN_HELP_SE:
			// �w���v���J��
			CheckAndStop(openHelp);
			break;

		case e_SCROLL_SE:
			// �X�N���[��
			CheckAndStop(scroll);
			break;

		case e_STAGE_CLEAR_SE:
			// �X�e�[�W�N���A
			CheckAndStop(stageClear);
			break;

		default:
			break;
	}
}

// ���ׂĂ�SE���~����
void Sound_SE::StopAllSE()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		StopSoundMem(SE[i]);
	}
}