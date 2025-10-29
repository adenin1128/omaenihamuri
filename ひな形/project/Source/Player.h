#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	Player(float startX, float startY);
	~Player();
	void Update() override;
	void Draw() override;
	int PlayerHP;
	VECTOR2 GetPosition() { return VECTOR2(x, y); }
	VECTOR2 GetColliderLeftTop() { return VECTOR2(x + colliderOffset, y + colliderOffset); }
	VECTOR2 GetColliderLeftBottom() { return VECTOR2(x + colliderOffset, y + CHARACTER_HEIGHT - colliderOffset); }
	VECTOR2 GetColliderRightTop() { return VECTOR2(x + CHARACTER_WIDTH - colliderOffset, y + colliderOffset); }
	VECTOR2 GetColliderRightBottom() { return VECTOR2(x + CHARACTER_WIDTH - colliderOffset, y + CHARACTER_HEIGHT - colliderOffset); }
private:
	static const int CHARACTER_WIDTH = 64;
	static const int CHARACTER_HEIGHT = 64;
	static const int ATLAS_WIDTH = 12;
	static const int ATLAS_HEIGHT = 1;
	static const int ANIM_FRAME_COUNT = 12;
	static const int ANIM_FRAME_INTERVAL = 4;   //  �A�j���[�V�����Ԋu(frame)
	static const int WALK_SPEED = 4;            //  �ړ����x(dot/frame)

	int animImage;      //  �A�j���[�V�����p�摜�n���h��
	int animIndex;      //  �ǂ��̃R�}��\�����邩
	int animFrame;      //  �A�j���[�V�����Ԋu
	int xPosition;      //  �L�����N�^�[��X���W
	bool direction;		//  �L�����N�^�[�̌���(true:������/false:�E����)

	int hImage;
	int posX ;
	int posY ;
	float x, y;
	float velocity;
	bool onGround;
	int jumpcount;
	int Maxjumpcount;

	int colliderOffset = 8;
};





