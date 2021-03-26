#pragma once

class SettingDxLib
{
private:
	static long long baseTime;				// ��ƂȂ鎞��
	static int refreshRate;					// ���t���b�V�����[�g
	static unsigned long long frequency;	// ���g��

	SettingDxLib();

	// ����������
	static void Initialize();

	// �X���[�v(Vsync���g�p����FPS���Œ�\)
	static void MySleep(int flag);
public:
	// DxLib�̏�����
	static bool InitDxLib();

	// DxLib�̕`�揈��
	static bool DrawDxLib();
};