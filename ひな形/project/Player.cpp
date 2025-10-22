#include "player.h"
#include "Field.h"
#include "DxLib.h"
#include "Trigger.h"
#include "Gameover.h"

static const float Gravity = 0.4;
static const float v0 = -10.0;


Player::Player(float startX, float startY) 
	: x(startX), y(startY), velocity(0.0f), onGround(false)
{   
	animImage = LoadGraph("data/image/���܂�����.png");
	posX = 100;
	posY = 100;
	jumpcount = 0;
	Maxjumpcount = 1;
	PlayerHP = 1;
	direction = true;
	int moveX = 1;
	animIndex = 0;       // �ŏ��̃R�}����X�^�[�g��������
	animFrame = 0;       // �A�j���[�V�����J�E���^�[�����Z�b�g�������
}

//�R���X�g���N�^�[
//�ŏ��Ɉ�񂾂��K���Ă΂��

//�f�X�g���N�^�[
//�Ō�Ɉ�x�����K���Ă΂��
Player::~Player()
{

}
//�v�Z����Ƃ���
void Player::Update()
{
	int moveX = 0;

	if (PlayerHP == 0) {
		new GameOver();
	}
	if (CheckHitKey(KEY_INPUT_R))
	{
		PlayerHP = 0;
	}
	if (onGround == true) {
		if(jumpcount < Maxjumpcount) {
			jumpcount += 1;
		}
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		x += 3.0f; // �E�ɐi�� 
		direction = false;
		moveX += 2.0f;
		Field* field = FindGameObject<Field>();
		int push1 = field->HitCheckRight(x + 50, y + 5);
		int push2 = field->HitCheckRight(x + 50, y + 61);
		x -= max(push1, push2);

	}

	if (CheckHitKey(KEY_INPUT_A)) {
		x -= 3.0f;
		direction = true;
		moveX -= 2.0f;
		Field* field = FindGameObject<Field>();
		int push1 = field->HitCheckLeft(x + 14, y + 5);
		int push2 = field->HitCheckLeft(x + 14, y + 61);
		x -= max(push1, push2);
	}

	if (onGround == true) {
		if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
			velocity = v0;
			onGround = false;
		}
	}

	if (onGround == false) {
		if (jumpcount == Maxjumpcount) {
			if (KeyTrigger::CheckTrigger(KEY_INPUT_SPACE)) {
				jumpcount -= 1;
				velocity = v0;
			}
		}
	}
	y += velocity;
	velocity += Gravity;
	if (velocity >= 0) {
		Field* field = FindGameObject<Field>();
		int push1 = field->HitCheckDown(x + 14, y + 64); // D�_�̉� 
		int push2 = field->HitCheckDown(x + 50, y + 64); // A�_�̉� 
		int push = max(push1, push2);
		if (push > 0) {
			y -= push - 1;
			velocity = 0;
			onGround = true;
		}
		else {
			onGround = false;
		}
	}
	else
	{
		Field* field = FindGameObject<Field>();
		int push1 = field->HitCheckUp(x + 14, y + 5); // D�_�̉� 
		int push2 = field->HitCheckUp(x + 50, y + 5); // A�_�̉� 
		int push = max(push1, push2);
		if (push > 0) {
			y += push;
			velocity = 0;
		}
	}
	if (moveX != 0)
	{
		// �ړ����̃A�j���[�V�����X�V
		animFrame = (animFrame + 1) % ANIM_FRAME_INTERVAL;
		if (animFrame == 0)
		{
			animIndex = (animIndex + 1) % ANIM_FRAME_COUNT;
		}

	}
	else
	{
		animIndex = 0; // �A�j���[�V�����̃R�}���ŏ��̃R�} (�Î~��) �ɌŒ肷��
    }
}


//�\������Ƃ���
void Player::Draw()
{
	Field* field = FindGameObject<Field>();	
	//DrawRectGraph(x, y, 0/*CHR_SIZE * pat*/, 0/*CHR_SIZE * dir*/, 64/*CHR_SIZE*/, 64/*CHR_SIZE*/, hImage, 1);
	//  �A�j���[�V�����̃R�}��TextureAtlas�̂ǂ��ɂ��邩�v�Z����
	int xRect = (animIndex % ATLAS_WIDTH) * CHARACTER_WIDTH;
	int yRect = (animIndex / ATLAS_WIDTH) * CHARACTER_HEIGHT;

	//  �L�����N�^�[��TextureAtlas���g���ĕ\������
	DrawRectGraph(x, y, xRect, yRect, CHARACTER_WIDTH, CHARACTER_HEIGHT, animImage, TRUE, direction);

	DrawFormatString(0, 100, GetColor(255, 255, 255), "X::%4f", x);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "y::%4f", y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "jumpcount::%d", jumpcount);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "PlayerHP::%d", PlayerHP);
}
