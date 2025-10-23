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
	animImage = LoadGraph("data/image/おまえ歩き.png");
	posX = 100;
	posY = 100;
	jumpcount = 0;
	Maxjumpcount = 1;
	PlayerHP = 1;
	direction = true;
	int moveX = 1;
	animIndex = 0;       // 最初のコマからスタートさせるやつ
	animFrame = 0;       // アニメーションカウンターをリセットしたやつ
}

//コンストラクター
//最初に一回だけ必ず呼ばれる

//デストラクター
//最後に一度だけ必ず呼ばれる
Player::~Player()
{

}
//計算するところ
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
		x += 3.0f; // 右に進む 
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
	if (moveX != 0)
	{
		// 移動時のアニメーション更新
		animFrame = (animFrame + 1) % ANIM_FRAME_INTERVAL;
		if (animFrame == 0)
		{
			animIndex = (animIndex + 1) % ANIM_FRAME_COUNT;
		}

	}
	else
	{
		animIndex = 0; // アニメーションのコマを最初のコマ (静止画) に固定する
    }
}


//表示するところ
void Player::Draw()
{
	Field* field = FindGameObject<Field>();	
	//DrawRectGraph(x, y, 0/*CHR_SIZE * pat*/, 0/*CHR_SIZE * dir*/, 64/*CHR_SIZE*/, 64/*CHR_SIZE*/, hImage, 1);
	//  アニメーションのコマがTextureAtlasのどこにあるか計算する
	int xRect = (animIndex % ATLAS_WIDTH) * CHARACTER_WIDTH;
	int yRect = (animIndex / ATLAS_WIDTH) * CHARACTER_HEIGHT;

	//  キャラクターをTextureAtlasを使って表示する
	DrawRectGraph(x, y, xRect, yRect, CHARACTER_WIDTH, CHARACTER_HEIGHT, animImage, TRUE, direction);

	DrawFormatString(0, 100, GetColor(255, 255, 255), "X::%4f", x);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "y::%4f", y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "jumpcount::%d", jumpcount);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "PlayerHP::%d", PlayerHP);
}
