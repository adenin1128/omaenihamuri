#pragma once
#include "../Library/GameObject.h"

// �v���C���[�̂��Ƃ���鏈���������Ƃ���
class Player : public GameObject
{
public:
	Player(); // �R���X�g���N�^�[�i�ŏ��ɂP��Ă΂��j
	~Player(); // �f�X�g���N�^�[�i�Ō�ɂP��Ă΂��j
	void Update() override; // ���t���[���Ă΂��@�v�Z
	void Draw() override; // ���t���[���Ă΂��@�`��

	// �����o�[�ϐ��i�v���C���[����������̂ɕK�v�ȕϐ�
	int image;
	float posX;
	float posY;
};