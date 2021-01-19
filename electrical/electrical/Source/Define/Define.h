#pragma once

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "ゲームタイトル";

// ウィンドウ横幅縦幅
const int WIN_WIDTH = 960;
const int WIN_HEIGHT = 540;

// マップチップサイズ
const int CHIP_SIZE = 56;

// ワールドサイズ
const int WORLD_WIDTH = 9600;
const int WORLD_HEIGHT = 2700;

// マップチップの数
const int MAP_COUNT_X = WORLD_WIDTH / CHIP_SIZE;
const int MAP_COUNT_Y = WORLD_HEIGHT / CHIP_SIZE;