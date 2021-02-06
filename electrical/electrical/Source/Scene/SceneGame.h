#pragma once

#include "SceneBase.h"
#include "../Character/Chara_Manager.h"
#include "../Stage/Stage.h"
#include "../Effect/EffectManager.h"
#include "../UI/UI_Manager.h"

class SceneGame:public SceneBase
{
private:
	Chara_Manager *characters;
	Stage *stage;
	EffectManager *effects;
	UI_Manager *ui;

	int scrollX;		// �X�N���[����
	int scrollY;		// �X�N���[����
	int screenX;		// �X�N���[�����S���W
	int screenY;		// �X�N���[�����S���W
	float displaceX;	// �X�N���[���̒��S�ɕ`�悷�邽�߂ɂ��炷��
	float displaceY;	// �X�N���[���̒��S�ɕ`�悷�邽�߂ɂ��炷��
	bool isScroll;		// �X�N���[���t���O
	bool isDrawUIMM;	// ������@UI�`��t���O

	float r;		// �ԐF				:0~255
	float g;		// �ΐF				:0~255
	float b;		// �F				:0~255
	float h;		// �F��(hue)			:0~360
	float s;		// �ʓx(saturation)	:0~255
	float v;		// ���x(value)		:0~255

	// �X�N���[�����W�̏���������
	void InitScrollPos();

	// �v���C���[�����i�s:-1,�E�i�s:1��Ԃ�
	int PlayerMoveLR();

	// �v���C���[����i�s:-1,���i�s:1��Ԃ�
	int PlayerMoveUD();

	// �X�N���[�����W�����߂�
	void CalcScreen();

	// �G�t�F�N�g�Ǘ�
	void MyEffectManager();

	// UI�Ǘ�
	void MyUIManager();

	// �V�[���J��
	void SceneChange(bool isSCPossible);

	// �Q�[���I��
	void GameEnd();

public:
	// �R���X�g���N�^
	SceneGame();

	// �f�X�g���N�^
	~SceneGame();

	// ����������
	void Initialize() override;

	// �X�V����
	void Update(bool isSCPossible) override;

	// �`�揈��
	void Draw() override;
};