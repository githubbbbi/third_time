#include "DxLib.h"
#include "Stage.h"

int Stage::mapData[][MAP_COUNT_X] = {
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

Stage::Stage(int mapGH[])
{
	for ( int i = 0; i < e_MAP_KIND_NUM; i++ )
	{
		this->mapGH[i] = mapGH[i];
	}

	graphIndex = 0;
}

// �X�V����
void Stage::Update()
{

}

// �}�b�v�`��
void Stage::MapDraw(int x, int y, float shakeX, float shakeY)
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
		DrawGraph(x * CHIP_SIZE + (int)shakeX,
				  y * CHIP_SIZE + (int)shakeX,
				  mapGH[graphIndex], true);
	}
}

// �`�揈��
void Stage::Draw(float shakeX, float shakeY)
{
	for ( int y = 0; y < MAP_COUNT_Y; y++ )
	{
		for ( int x = 0; x < MAP_COUNT_X; x++ )
		{
			MapDraw(x, y, shakeX, shakeY);
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