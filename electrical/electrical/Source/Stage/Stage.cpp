#include "DxLib.h"
#include "Stage.h"
#include "../Resource/Graphic.h"
#include "../Resource/CSV.h"

int Stage::mapData[MAP_COUNT_Y][MAP_COUNT_X] = { 0 };

Stage::Stage()
{
	graphIndex = 0;
}

// ����������
bool Stage::Initialize()
{
	// �ǂݍ��ރt�@�C�������i�[����
	char fileName[512];
	sprintf_s(fileName, sizeof(fileName),
			  "Resource/Data/Stage/stage%d.csv", 1);

	// �t�@�C�����ǂݍ��߂Ȃ��ꍇ�Afalse
	int *p = (int *)mapData;
	if ( !CSV::LoadFile(fileName, MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// �}�b�v�`��
void Stage::MapDraw(int x, int y,
					float shakeX, float shakeY, int scrollX, int scrollY)
{
	switch ( mapData[y][x] )
	{
		case e_MAP_NONE:
			// �Ȃ�
			graphIndex = e_MAP_NONE;
			break;

		case e_MAP_BLOCK:
			// �u���b�N
			graphIndex = e_MAP_BLOCK;
			break;
		
		case e_MAP_GOAL:
			// �S�[��
			graphIndex = e_MAP_GOAL;
			break;

		default:
			graphIndex = e_MAP_NONE;
			break;
	}

	if ( graphIndex != e_MAP_NONE )
	{
		DrawGraph(x * CHIP_SIZE + (int)shakeX - scrollX,
				  y * CHIP_SIZE + (int)shakeX - scrollY,
				  Graphic::GetInstance()->GetMap(graphIndex), true);
	}
}

// �`�揈��
void Stage::Draw(float shakeX, float shakeY,
				 int scrollX, int scrollY, int screenX, int screenY)
{
	// �X�N���[���ɉf���Ă��镔��������`��
	int mapChipLeft = (screenX - WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipRight = (screenX + WIN_WIDTH / 2) / CHIP_SIZE;
	int mapChipTop = (screenY - WIN_HEIGHT / 2) / CHIP_SIZE;
	int mapChipBottom = (screenY + WIN_HEIGHT / 2) / CHIP_SIZE;

	for ( int y = mapChipTop; y < mapChipBottom; y++ )
	{
		for ( int x = mapChipLeft; x < mapChipRight; x++ )
		{
			MapDraw(x, y, shakeX, shakeY, scrollX, scrollY);
		}
	}
}

// �}�b�v�`�b�v�̒l���擾
int Stage::GetMapParam(float x, float y)
{
	// �}�b�v�`�b�v�z��̓Y����
	int mapX = (int)x / CHIP_SIZE;
	int mapY = (int)y / CHIP_SIZE;

	// �}�b�v����o�Ă����ꍇ�ANONE��Ԃ�
	if ( mapX < 0 || mapY < 0 ||
		mapX >= MAP_COUNT_X ||
		mapY >= MAP_COUNT_Y )
	{
		return e_MAP_NONE;
	}

	// �}�b�v�`�b�v�z��̒l��Ԃ�
	return mapData[mapY][mapX];
}