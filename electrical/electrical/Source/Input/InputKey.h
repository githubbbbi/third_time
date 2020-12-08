#pragma once

// 最新のキーボード情報用
static char keys[256];

// 1ループ(フレーム)前のキーボード情報
static char oldkeys[256];

// 初期化処理
void KeyInit();

// 更新処理
void KeyUpdate();

// 前フレームが押されていない状態から押された場合TRUE
bool IsKeyInputNow(int key);

// 押されていて離された瞬間TRUE
bool IsKeyInputRelease(int key);