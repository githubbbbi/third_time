#pragma once

class Effect_Explosion
{
private:
	float x;
	float y;
	bool isActive;

	int particleGH;

public:
	Effect_Explosion(float x, float y, int particleGH);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);

	// isActiveを取得
	bool GetIsActive();
};