#include <stdio.h>
#include <stdlib.h>
#include "CSV.h"

bool CSV::LoadFile(const char *fileName,
				   int x, int y, int *data)
{
	// ファイルを開く
	FILE *fp;
	fopen_s(&fp, fileName, "r");

	// ファイルが開けないもしくは存在しない
	if ( fp == nullptr )
	{
		return false;
	}

	char buf[1024];	// 文字列を格納
	char *str;		// 変換対象の文字列を格納
	char *end;		// 変換終了した位置を格納

	// データを読み込む
	for ( int yy = 0; yy < y; yy++ )
	{
		fgets(buf, sizeof(buf), fp);	// 1行読み込む(','を含む)
		str = buf;						// 変換する文字列を代入(','を含む)

		for ( int xx = 0; xx < x; xx++ )
		{
			data[yy * x + xx] = strtol(str, &end, 10);	// 文字列を10進数に変換
			str = end + 1;								// ','をスキップ
		}
	}

	// ファイルを閉じる
	fclose(fp);

	// 終了
	return true;
}