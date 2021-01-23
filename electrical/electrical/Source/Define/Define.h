#pragma once

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "ゲームタイトル";

// ウィンドウ横幅縦幅
const int WIN_WIDTH = 56 * 17;
const int WIN_HEIGHT = 56 * 9;

// マップチップサイズ
const int CHIP_SIZE = 56;

// マップ(ワールド)サイズ
const int MAP_WIDTH = 9600;
const int MAP_HEIGHT = 2700;

// マップチップの数
const int MAP_COUNT_X = MAP_WIDTH / CHIP_SIZE - 1;
const int MAP_COUNT_Y = MAP_HEIGHT / CHIP_SIZE;