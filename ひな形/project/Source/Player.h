#pragma once
#include "../Library/GameObject.h"

enum PlayerState {
	STATE_NORMAL,    // �ʏ펞
	STATE_BOOM, // ���Ē�
	STATE_GAMEOVER   // ��ʊO�ɏo�ăQ�[���I�[�o�[
};

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
	float velX;          // X�����̑��x (BOOM�p)
	float velY;          // Y�����̑��x (BOOM�p)
	float rot;           // ��]�p�x (BOOM�̃v���C���[���邮��p)
	PlayerState state;   // �v���C���[�̏�ԊǗ�
	float GetX() const { return x; }
	float GetY() const { return y; }
	// ���x�Ə�Ԃ�ݒ肷��
	void SetBOOM(float vx, float vy) {
		velX = vx;
		velY = vy;
		rot = 0.0f; // ������]�����Z�b�g
		state = STATE_BOOM;
	}
	PlayerState GetState() const { return state; }
	void SetState(PlayerState s) { state = s; }
	// Player.h �� public: �Z�N�V�����ɉ���Œǉ�
	bool IsBOOM() const { return state == STATE_BOOM; }

private:

	static const int CHARACTER_WIDTH = 64;
	static const int CHARACTER_HEIGHT = 64;
	static const int ATLAS_WIDTH = 12;
	static const int ATLAS_HEIGHT = 1;
	static const int BOOM_CHARACTER_WIDTH = 64;
	static const int BOOM_CHARACTER_HEIGHT = 64;
	static const int BOOM_ATLAS_WIDTH = 36;
	static const int BOOM_ATLAS_HEIGHT = 1;
	static const int BOOM_ANIM_FRAME_COUNT = 36;
	static const int BOOM_ANIM_FRAME_INTERVAL = 4;
	static const int ANIM_FRAME_COUNT = 12;
	static const int ANIM_FRAME_INTERVAL = 4;   //  �A�j���[�V�����Ԋu(frame)
	static const int WALK_SPEED = 4;            //  �ړ����x(dot/frame)

	int animImage;      //  �A�j���[�V�����p�摜�n���h��
	int animIndex;      //  �ǂ��̃R�}��\�����邩
	int animFrame;      //  �A�j���[�V�����Ԋu
	int xPosition;      //  �L�����N�^�[��X���W
	bool direction;		//  �L�����N�^�[�̌���(true:������/false:�E����)
	int BOOMImage;      //  ���ėp�摜�n���h��
	int boomAnimIndex;  //  ���ăA�j���[�V�����̃R�}
	int boomFrame;      //  ���ăA�j���[�V�����Ԋu


	int hImage;
	int posX;
	int posY;
	float x, y;
	float velocity;
	bool onGround;
	int jumpcount;
	int Maxjumpcount;

	int colliderOffset = 8;
};





