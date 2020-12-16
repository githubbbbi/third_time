#pragma once

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "ゲームタイトル";

// ウィンドウ横幅縦幅
const int WIN_WIDTH = 960;
const int WIN_HEIGHT = 540;

// マップチップサイズ
const int CHIP_SIZE = 64;

// マップチップの数
const int MAP_COUNT_X = WIN_WIDTH / CHIP_SIZE;
const int MAP_COUNT_Y = WIN_HEIGHT / CHIP_SIZE + 1;