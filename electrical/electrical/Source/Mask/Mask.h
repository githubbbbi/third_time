#pragma once

class Mask
{
private:
	static int screenHandle;

	static double sizeRate;

public:
	// マスクのセット
	static void SetMask();

	// マスクの収縮
	static void MaskShrink();

	// マスクの描画
	static void DrawMask();

	// マスクの後処理
	static void LoopMask();
};