#include <stdio.h>
#include <stdlib.h>
#include "CSV.h"

bool CSV::LoadFile(const char *fileName,
				   int num, int x, int y, int *data)
{
	// �ǂݍ��ރt�@�C�������i�[����
	char file[512];
	sprintf_s(file, sizeof(file), fileName, num);

	// �t�@�C�����J��
	FILE *fp;
	fopen_s(&fp, file, "r");

	// �t�@�C�����J���Ȃ��������͑��݂��Ȃ�
	if ( fp == nullptr )
	{
		return false;
	}

	char buf[1024];	// ��������i�[
	char *str;		// �ϊ��Ώۂ̕�������i�[
	char *end;		// �ϊ��I�������ʒu���i�[

	// �f�[�^��ǂݍ���
	for ( int yy = 0; yy < y; yy++ )
	{
		fgets(buf, sizeof(buf), fp);	// 1�s�ǂݍ���(','���܂�)
		str = buf;						// �ϊ����镶�������(','���܂�)

		for ( int xx = 0; xx < x; xx++ )
		{
			data[yy * x + xx] = strtol(str, &end, 10);	// �������10�i���ɕϊ�
			str = end + 1;								// ','���X�L�b�v
		}
	}

	// �t�@�C�������
	fclose(fp);

	// �I��
	return true;
}