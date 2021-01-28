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
	ChangeVolumeSoundMem((int)(255.0f * 90.0f / 100.0f), receiveDamage);
	ChangeVolumeSoundMem((int)(255.0f * 50.0f / 100.0f), openHelp);
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

// SE�Đ�
void Sound_SE::PlaySE(SE_Info se, bool isCheckSound)
{
	switch ( se )
	{
		case e_GAME_START_SE:
			// �Q�[���X�^�[�g
			if ( isCheckSound &&
				CheckSoundMem(gameStart) )
			{
				break;
			}

			PlaySoundMem(gameStart, DX_PLAYTYPE_BACK);
			break;

		case e_PLAYER_JUMP_SE:
			// �v���C���[�̃W�����v
			if ( isCheckSound &&
				CheckSoundMem(playerJump) )
			{
				break;
			}

			PlaySoundMem(playerJump, DX_PLAYTYPE_BACK);
			break;

		case e_PLAYER_CHAGING_SE:
			// �[�d��
			if ( isCheckSound &&
				CheckSoundMem(playerCharging) )
			{
				break;
			}

			PlaySoundMem(playerCharging, DX_PLAYTYPE_BACK);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// �d�C�e������
			if ( isCheckSound &&
				CheckSoundMem(shotElectricGun) )
			{
				break;
			}

			PlaySoundMem(shotElectricGun, DX_PLAYTYPE_BACK);
			break;

		case e_SHOT_WATER_GUN_SE:
			// ���e������
			if ( isCheckSound &&
				CheckSoundMem(shotWaterGun) )
			{
				break;
			}

			PlaySoundMem(shotWaterGun, DX_PLAYTYPE_BACK);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// �_���[�W���󂯂�
			if ( isCheckSound &&
				CheckSoundMem(receiveDamage) )
			{
				break;
			}

			PlaySoundMem(receiveDamage, DX_PLAYTYPE_BACK);
			break;

		case e_DEATH_SE:
			// ���S
			if ( isCheckSound &&
				CheckSoundMem(death) )
			{
				break;
			}

			PlaySoundMem(death, DX_PLAYTYPE_BACK);
			break;

		case e_OPEN_HELP_SE:
			// �w���v���J��
			if ( isCheckSound &&
				CheckSoundMem(openHelp) )
			{
				break;
			}

			PlaySoundMem(openHelp, DX_PLAYTYPE_BACK);
			break;
		
		case e_SCROLL_SE:
			// �X�N���[��
			if ( isCheckSound &&
				CheckSoundMem(scroll) )
			{
				break;
			}

			PlaySoundMem(scroll, DX_PLAYTYPE_BACK);
			break;
		
		case e_STAGE_CLEAR_SE:
			// �X�e�[�W�N���A
			if ( isCheckSound &&
				CheckSoundMem(stageClear) )
			{
				break;
			}

			PlaySoundMem(stageClear, DX_PLAYTYPE_BACK);
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
			if ( !CheckSoundMem(gameStart) )
			{
				break;
			}

			StopSoundMem(gameStart);
			break;

		case e_PLAYER_JUMP_SE:
			// �v���C���[�̃W�����v
			if ( !CheckSoundMem(playerJump) )
			{
				break;
			}

			StopSoundMem(playerJump);
			break;

		case e_PLAYER_CHAGING_SE:
			// �[�d��
			if ( !CheckSoundMem(playerCharging) )
			{
				break;
			}

			StopSoundMem(playerCharging);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// �d�C�e������
			if ( !CheckSoundMem(shotElectricGun) )
			{
				break;
			}

			StopSoundMem(shotElectricGun);
			break;

		case e_SHOT_WATER_GUN_SE:
			// ���e������
			if ( !CheckSoundMem(shotWaterGun) )
			{
				break;
			}

			StopSoundMem(shotWaterGun);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// �_���[�W���󂯂�
			if ( !CheckSoundMem(receiveDamage) )
			{
				break;
			}

			StopSoundMem(receiveDamage);
			break;

		case e_DEATH_SE:
			// ���S
			if ( !CheckSoundMem(death) )
			{
				break;
			}

			StopSoundMem(death);
			break;

		case e_OPEN_HELP_SE:
			// �w���v���J��
			if ( !CheckSoundMem(openHelp) )
			{
				break;
			}

			StopSoundMem(openHelp);
			break;

		case e_SCROLL_SE:
			// �X�N���[��
			if ( !CheckSoundMem(scroll) )
			{
				break;
			}

			StopSoundMem(scroll);
			break;

		case e_STAGE_CLEAR_SE:
			// �X�e�[�W�N���A
			if ( !CheckSoundMem(stageClear) )
			{
				break;
			}

			StopSoundMem(stageClear);
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