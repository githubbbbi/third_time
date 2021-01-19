#pragma once

#include "../Define/Define.h"

// �}�b�v�`�b�v�ɑΉ�����l
enum MapChip
{
	e_MAP_NONE = -1,	// �Ȃ�
	e_MAP_BLOCK,		// �u���b�N
	e_MAP_FIELD,		// �e�X�g�p
	e_MAP_NUM			// ���
};

class Stage
{
private:
	int graphIndex;

	static int mapData[MAP_COUNT_Y][MAP_COUNT_X];

	// �}�b�v�`��
	void MapDraw(int x, int y, float shakeX, float shakeY, int scrollX, int scrollY);

public:
	Stage();

	// ����������
	bool Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	//�}�b�v�`�b�v�̒l���擾
	static int GetMapParam(float x, float y);
};