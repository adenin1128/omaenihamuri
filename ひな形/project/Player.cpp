#include "player.h"
#include "Field.h"
#include "DxLib.h"
#include "Trigger.h"

static const float Gravity = 0.4;
static const float v0 = -10.0;
//コンストラクター
//最初に一回だけ必ず呼ばれる
Player::Player(float startX, float startY)
    : x(startX), y(startY), velocity(0.0f), onGround(false)
{
    hImage = LoadGraph("data/image/aoi.png");
	jumpcount = 0;
	Maxjumpcount = 1;
}
//デストラクター
//最後に一度だけ必ず呼ばれる
Player::~Player()
{

}
//計算するところ
void Player::Update()
{
	if (onGround == true) {
		if(jumpcount < Maxjumpcount) {
			jumpcount += 1;
		}
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		x += 2.0f; // 右に進む 
		Field* field = FindGameObject<Field>();
		int push1 = field->HitCheckRight(x + 50, y + 5);
		int push2 = field->HitCheckRight(x + 50, y + 61);
		x -= max(push1, push2);

	}
	if (CheckHitKey(KEY_INPUT_A)) {
		x -= 2.0f;
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
		int push1 = field->HitCheckDown(x + 14, y + 64); // D点の下 
		int push2 = field->HitCheckDown(x + 50, y + 64); // A点の下 
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
		int push1 = field->HitCheckUp(x + 14, y + 5); // D点の下 
		int push2 = field->HitCheckUp(x + 50, y + 5); // A点の下 
		int push = max(push1, push2);
		if (push > 0) {
			y += push;
			velocity = 0;
		}
	}

}
//表示するところ
void Player::Draw()
{
	Field* field = FindGameObject<Field>();	
	DrawRectGraph(x,y,0,0,64,64, hImage, 1);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "X::%4f", x);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "y::%4f", y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "jumpcount::%d", jumpcount);
}
