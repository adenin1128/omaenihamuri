#include "player.h"
#include "Field.h"
#include "DxLib.h"
#include "Trigger.h"
#include "Gameover.h"
#include "trap.h"


static const float Gravity = 0.4;
static const float v0 = -10.0;

const float DRAG_COEFFICIENT = 0.05f;  // ���x�̌����W��
const float ROT_SPEED = 0.0f;          // ��]���x
const int SAFE_MARGIN = 100;           // ��ʊO����}�[�W��



Player::Player(float startX, float startY)
	: x(startX), y(startY), velocity(0.0f), onGround(false)
{
	animImage = LoadGraph("data/image/���܂�����.png");
	BOOMImage = LoadGraph("data/image/BOOM!!.png");
	posX = 100;
	posY = 100;
	jumpcount = 0;
	Maxjumpcount = 1;
	PlayerHP = 1;
	direction = true;
	int moveX = 1;
	animIndex = 0;       // �ŏ��̃R�}����X�^�[�g��������
	animFrame = 0; // �A�j���[�V�����J�E���^�[�����Z�b�g�������
	state = STATE_NORMAL;
	boomAnimIndex = 0;
	boomFrame = 0;

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
	if (state == STATE_NORMAL) {
		int moveX = 0;

		if (PlayerHP == 0) {
			new GameOver();
		}
		if (CheckHitKey(KEY_INPUT_R))
		{
			PlayerHP = 0;
		}
		if (onGround == true) {
			if (jumpcount < Maxjumpcount) {
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
			if (field->Istrap(x + 32, y + 32)) {
				/*new Clear();*/
			}
		}

		if (CheckHitKey(KEY_INPUT_A)) {
			x -= 3.0f;
			direction = true;
			moveX -= 2.0f;
			Field* field = FindGameObject<Field>();
			int push1 = field->HitCheckLeft(x + 14, y + 5);
			int push2 = field->HitCheckLeft(x + 14, y + 61);
			x -= max(push1, push2);
			if (field->Istrap(x + 32, y + 32)) {
				/*new Clear();*/
			}
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
	if (state == STATE_BOOM) {

		const float deltaTime = 20.0f / 60.0f;

		// 1. ���x�̌���
		velX *= (1.0f - DRAG_COEFFICIENT);
		velY *= (1.0f - DRAG_COEFFICIENT);

		// 2. �ʒu�̍X�V
		x += velX * deltaTime;
		y += velY * deltaTime;

		// 3. anime�̍X�V


		// 4. ��ʊO����
		if (x < -SAFE_MARGIN || x > 1920 + SAFE_MARGIN ||
			y < -SAFE_MARGIN || y > 1080 + SAFE_MARGIN)//�V�[���̕��ƍ���������
		{
			boomFrame = (boomFrame + 1) % BOOM_ANIM_FRAME_INTERVAL;
			if (boomFrame == 0)
			{
				boomAnimIndex = (boomAnimIndex + 1) % BOOM_ANIM_FRAME_COUNT;
			}
			// ��ʊO�ɏo����Q�[���I�[�o�[�����ֈڍs
			state = STATE_GAMEOVER;
			new GameOver(); // �����ŏ��߂ăQ�[���I�[�o�[��ʂֈڍs����悤�ɂ�����
		}
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
	int boomXRect = (boomAnimIndex % BOOM_ATLAS_WIDTH) * BOOM_CHARACTER_WIDTH;
	int boomYRect = (boomAnimIndex / BOOM_ATLAS_WIDTH) * BOOM_CHARACTER_HEIGHT;

	//  �L�����N�^�[��TextureAtlas���g���ĕ\������
	if (state == STATE_BOOM) {

		DrawRectGraph(x, y, boomXRect, boomYRect, 64, 64, BOOMImage, TRUE, direction);
	}
	else {
		DrawRectGraph(x, y, xRect, yRect, CHARACTER_WIDTH, CHARACTER_HEIGHT, animImage, TRUE, direction);
	}
	// �f�o�b�O�p���\��
	DrawFormatString(0, 100, GetColor(255, 255, 255), "X::%4f", x);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "y::%4f", y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "jumpcount::%d", jumpcount);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "PlayerHP::%d", PlayerHP);

	// �f�o�b�O�p�����蔻��\��
	DrawCircle(GetColliderLeftTop().x, GetColliderLeftTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderLeftBottom().x, GetColliderLeftBottom().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightTop().x, GetColliderRightTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightBottom().x, GetColliderRightBottom().y, 2, GetColor(0, 255, 0), true);
}
