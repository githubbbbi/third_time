#pragma once

class UI_Ready
{
private:
	int x;			// ���S���W
	int y;			// ���S���W
	bool isReady;	// READY�t���O

public:
	UI_Ready();
	~UI_Ready() = default;

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// isReady���擾
	bool GetIsReady();
};