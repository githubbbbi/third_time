#pragma once

class UI_ManipulationMethod
{
private:
	int x;			// ���S���W
	int y;			// ���S���W
	int graphIndex;	// �O���t�C���f�b�N�X

public:
	UI_ManipulationMethod();
	~UI_ManipulationMethod() = default;

	// �X�V����
	void Update(bool isDrawUIMM);

	// �`�揈��
	void Draw(bool isDrawUIMM);
};