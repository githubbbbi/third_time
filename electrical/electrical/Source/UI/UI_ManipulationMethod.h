#pragma once

class UI_ManipulationMethod
{
private:
	typedef struct
	{
		int x;			// ���S���W
		int y;			// ���S���W
		int graphIndex;	// �O���t�C���f�b�N�X
	}UI;

	UI ui[2];

public:
	UI_ManipulationMethod();
	~UI_ManipulationMethod() = default;

	// �X�V����
	void Update(bool isDrawUIMM);

	// �`�揈��
	void Draw(bool isDrawUIMM);
};