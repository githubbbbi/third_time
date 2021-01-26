#pragma once

class Effect_Lightning
{
private:
	// ü
	int posX;
	int posY;
	int posX2;
	int posY2;
	int oldPosX;
	int oldPosY;
	int oldPosX2;
	int oldPosY2;

	// •ûŒü
	int valX;
	int valY;

	// ”½Ë•Ç‚ÌÀ•W
	int wallX;
	int wallY;
	int wallX2;
	int wallY2;

	int timer;

public:
	Effect_Lightning(int wallX,int wallY,int wallX2,int wallY2);
	~Effect_Lightning() = default;

	// ”ò‹——£
	bool IsLengthOver();

	// XVˆ—
	void Update();

	// ˆÚ“®
	void Move();

	// ”½Ë
	void LightningCollision();

	// •`‰æˆ—
	void Draw();
};