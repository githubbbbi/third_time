#pragma once

// �^�C�g����p��UI�N���X
class UI_Title
{
private:
	int x;				// ���S���W
	int y;				// ���S���W
	int trasparency;	// ���ߓx

public:
	UI_Title();
	~UI_Title() = default;

	// �X�V����
	void Update(bool isBlinking, bool isFlashing);

	// �`�揈��
	void Draw();
};