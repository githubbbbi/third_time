#pragma once

#include "../Define/Define.h"

// �}�b�v�`�b�v�ɑΉ�����l
enum MapChip
{
	e_MAP_NONE = -1,			// �Ȃ�
	e_MAP_BLOCK,				// �u���b�N
	e_MAP_GOAL_LEFT_BOTTOM,		// �S�[������
	e_MAP_GOAL_RIGHT_BOTTOM,	// �S�[���E��
	e_MAP_GOAL_LEFT_TOP,		// �S�[������
	e_MAP_GOAL_RIGHT_TOP,		// �S�[������
	e_MAP_NUM,					// �}�b�v�`�b�v��
	e_MAP_GOAL					// �S�[��
};

class Stage
{
private:
	int graphIndex;

	static int mapData[MAP_COUNT_Y][MAP_COUNT_X];

	// �}�b�v�`��
	void MapDraw(int x, int y, float shakeX, float shakeY,
				 int scrollX, int scrollY, int displaceX, int displaceY);

public:
	Stage();

	// ����������
	bool Initialize();

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY,
			  int screenX, int screenY, int displaceX, int displaceY);

	//�}�b�v�`�b�v�̒l���擾
	static int GetMapParam(float x, float y);
};