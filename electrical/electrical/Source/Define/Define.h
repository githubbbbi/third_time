#pragma once

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "CHARGING";

// �E�B���h�E�����c��
const int WIN_WIDTH = 960;
const int WIN_HEIGHT = 540;

// �}�b�v�`�b�v�T�C�Y
const int CHIP_SIZE = 56;

// �}�b�v(���[���h)�T�C�Y
const int MAP_WIDTH = 9600;
const int MAP_HEIGHT = 2700;

// �}�b�v�`�b�v�̐�
const int MAP_COUNT_X = MAP_WIDTH / CHIP_SIZE - 1;
const int MAP_COUNT_Y = MAP_HEIGHT / CHIP_SIZE;

// �����T�C�Y
const int ROOM_SIZE_X = 17 * CHIP_SIZE;
const int ROOM_SIZE_Y = 9 * CHIP_SIZE;

// (�E�B���h�E�T�C�Y - �����T�C�Y) / 2 = ��ʏ�����Ƃ������炷��
const int DISPLACE_X = (WIN_WIDTH - ROOM_SIZE_X) / 2;
const int DISPLACE_Y = (WIN_HEIGHT - ROOM_SIZE_Y) / 2;