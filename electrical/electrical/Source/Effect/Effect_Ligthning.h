#pragma once

class Effect_Lightning
{
private:
	// �������������ɕϐ��錾


public:
	Effect_Lightning(int x1, int y1, int x2, int y2);
	~Effect_Lightning() = default;

	// �򋗗�
	bool IsLengthOver();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();
};