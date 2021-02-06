#pragma once

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "CHARGING";

// ウィンドウ横幅縦幅
const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

// マップチップサイズ
const int CHIP_SIZE = 56;

// マップ(ワールド)サイズ
const int MAP_WIDTH = 9600;
const int MAP_HEIGHT = 2700;

// マップチップの数
const int MAP_COUNT_X = MAP_WIDTH / CHIP_SIZE - 1;
const int MAP_COUNT_Y = MAP_HEIGHT / CHIP_SIZE;

// 部屋サイズ
const int ROOM_SIZE_X = 17 * CHIP_SIZE;
const int ROOM_SIZE_Y = 9 * CHIP_SIZE;

// (ウィンドウサイズ - 部屋サイズ) / 2 = 画面上を軸としたずらす量
const int DISPLACE_X = (WIN_WIDTH - ROOM_SIZE_X) / 2;
const int DISPLACE_Y = (WIN_HEIGHT - ROOM_SIZE_Y) / 2;