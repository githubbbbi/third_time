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
	// �t�@�C�����ǂݍ��߂Ȃ��ꍇ�Afalse
	int *p = (int *)mapData;
	if ( !CSV::LoadFile("Resource/Data/Stage/stage%d.csv",
						1, MAP_COUNT_X, MAP_COUNT_Y, p) )
	{
		return false;
	}

	return true;
}

// �X�V����
void Stage::Update()
{

}

// �}�b�v�`��
void Stage::MapDraw(int x, int y, float shakeX, float shakeY, int scrollX, int scrollY)
{
	switch ( mapData[y][x] )
	{
		case e_MAP_NONE:
			// �Ȃ�
			graphIndex = e_MAP_NONE;
			break;

		case e_MAP_BLOCK:
			// �u���b�N
			graphIndex = 0;
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
void Stage::Draw(float shakeX, float shakeY, int scrollX, int scrollY)
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			MapDraw(x, y, shakeX, shakeY, scrollX, scrollY);
		}
	}
}

// �}�b�v�`�b�v�̒l���擾
int Stage::GetMapParam(float x, float y)
{
	// �}�b�v�`�b�v�z��̓Y����
	int mapX, mapY;

	mapX = (int)x / CHIP_SIZE;
	mapY = (int)y / CHIP_SIZE;

	// �}�b�v����o�Ă����ꍇ�A-1��Ԃ�
	if ( mapX < 0 || mapY < 0 ||
		mapX >= MAP_COUNT_X ||
		mapY >= MAP_COUNT_Y )
	{
		return -1;
	}

	// �}�b�v�`�b�v�z��̒l��Ԃ�
	return mapData[mapY][mapX];
}