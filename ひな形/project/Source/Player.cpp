#include "player.h"
#include "Field.h"
#include "DxLib.h"
#include "Trigger.h"
#include "Gameover.h"
#include "trap.h"
#include "Nyoki.h"
#include "skeleton.h"
#include "Clear.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Debug.h"

static float Gravity = 0.4;
static const float v0 = -10.0;

const float DRAG_COEFFICIENT = 0.05f;  // 速度の減衰係数
const float ROT_SPEED = 0.0f;          // 回転速度
const int SAFE_MARGIN = 100;           // 画面外判定マージン

int boomGraphs[36];


Player::Player(float startX, float startY)
	: resetX(startX), resetY(startY), velocity(0.0f), onGround(false)
{
	animImage = LoadGraph("data/image/おまえ歩き.png");
	BOOMImage = LoadGraph("data/image/BOOM!!.png");
	LoadDivGraph("data/image/BOOM!!.png", 37, 37, 1, 64, 64, boomGraphs);
	loseImage = LoadGraph("data/image/you lose.png");

	Reset();
}

//コンストラクター
//最初に一回だけ必ず呼ばれる

//デストラクター
//最後に一度だけ必ず呼ばれる
Player::~Player()
{

}

void Player::Reset(int px, int py)
{
	resetX = px;
	resetY = py;
	Reset();
}

void Player::Reset()
{
	x = resetX;
	y = resetY;
	velocity = 0.0f;
	onGround = false;
	posX = 100;
	posY = 100;
	jumpcount = 0;
	Maxjumpcount = 1;
	PlayerHP = 1;
	direction = true;
	int moveX = 1;
	animIndex = 0;       // 最初のコマからスタートさせるやつ
	animFrame = 0; // アニメーションカウンターをリセットしたやつ
	state = STATE_NORMAL;
	boomAnimIndex = 0;
	boomFrame = 0;
	Boomtime = 0;
	speed = 0;
	new Debug();
	/*x = 500;
	y = 200;*/
}

//計算するところ
void Player::Update()
{
	Field* field = FindGameObject<Field>();
	field->IsGate(x, y);
	field->IsBelt(x, y);
	// Nyokiの左右判定
	Nyoki* nyoki = FindGameObject<Nyoki>();
	if (nyoki != nullptr) {
		int push1, push2;
		push1 = nyoki->HitCheckRight(x + 55, y + 9);
		push2 = nyoki->HitCheckRight(x + 55, y + 55);
		x -= max(push1, push2);
		
		push1 = nyoki->HitCheckLeft(x + 9, y + 9);
		push2 = nyoki->HitCheckLeft(x + 9, y + 55);
		x -= min(push1, push2);
	}

	if (state == STATE_NORMAL) {
		int moveX = 0;

		if (onGround == true) {
			if (jumpcount < Maxjumpcount) {
				jumpcount += 1;
			}
		}

		if(CheckHitKey(KEY_INPUT_R)) {
			Gravity = 0.4;
		}

		if (CheckHitKey(KEY_INPUT_T)) {
			Gravity = 0.4;
		}

		if (CheckHitKey(KEY_INPUT_D))
		{
			x += 3.0f + speed; // 右に進む 
			direction = false;
			moveX += 2.0f;
			
			// Field判定
			Field* field = FindGameObject<Field>();
			int push1 = field->HitCheckRight(x + 55, y + 5);
			int push2 = field->HitCheckRight(x + 55, y + 61);
			int push3 = field->HitCheckRight(x + 55, y + 28);
			x -= max(push1, push2, push3);
			field->Istrap(x + 32, y + 32);
			field->IsNyoki(x + 32, y + 32);
			field->Jetpack(x, y);
			field->IsGate(x, y);
			field->IsBelt(x, y);
			speed = 0;
		}

		if (CheckHitKey(KEY_INPUT_A)) {
			x -= 3.0f + speed;
			direction = true;
			moveX -= 2.0f;

			// Field判定
			Field* field = FindGameObject<Field>();
			int push1 = field->HitCheckLeft(x + 9, y + 5);
			int push2 = field->HitCheckLeft(x + 9, y + 61);
			int push3 = field->HitCheckLeft(x + 9, y + 28);

			x -= max(push1, push2, push3);
			field->Istrap(x + 32, y + 32);
			field->IsNyoki(x + 32, y + 32);
			field->Jetpack(x, y);
			field->IsGate(x, y);
			field->IsBelt(x, y);
			speed = 0;
		}

		Field* j = FindGameObject<Field>();
		if (j->GetJetpack() == true) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				velocity = v0;
			}
		}
		else if (j->GetJetpack() == false) {
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
		}
	
		y += velocity;
		velocity += Gravity;
		if (velocity >= 0) {
			// Field判定
			Field* field = FindGameObject<Field>();
			int push1 = field->HitCheckDown(x + 9, y + 64); // D点の下 
			int push2 = field->HitCheckDown(x + 55, y + 64); // A点の下 
			int push3 = field->HitCheckDown(x + 28, y + 64);

			// Nyoki判定を追加
			Nyoki* nyoki = FindGameObject<Nyoki>();
			if (nyoki != nullptr) {
				push1 = max(push1, nyoki->HitCheckDown(x + 9, y + 64));
				push2 = max(push2, nyoki->HitCheckDown(x + 55, y + 64));
				push3 = max(push3, nyoki->HitCheckDown(x + 28, y + 64));
			}

			int push = max(push1, push2, push3);
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
			// Field判定
			Field* field = FindGameObject<Field>();
			int push1 = field->HitCheckUp(x + 9, y + 5); // D点の下 
			int push2 = field->HitCheckUp(x + 55, y + 5); // A点の下
			int push3 = field->HitCheckUp(x + 28, y + 5);

			// Nyoki判定を追加
			Nyoki* nyoki = FindGameObject<Nyoki>();
			if (nyoki != nullptr) {
				push1 = max(push1, nyoki->HitCheckUp(x + 9, y + 5));
				push2 = max(push2, nyoki->HitCheckUp(x + 55, y + 5));
				push3 = max(push3, nyoki->HitCheckUp(x + 28, y + 5));
			}

			int push = max(push1, push2, push3);
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
		Field* field = FindGameObject<Field>();
		if (field->IsGoal(x, y)) {
			new Clear();
			state = STATE_CLEAR;
			field->SetClear();
			DeleteGraph(animImage);
		}
		if (field->IsNyoki(x, y)) {

		}
	}
	if (state == STATE_BOOM) {

		const float deltaTime = 55.0f / 60.0f;

		// 1. 速度の減衰
		velX *= (1.0f - DRAG_COEFFICIENT);
		velY *= (1.0f - DRAG_COEFFICIENT);

		// 2. 位置の更新
		x += velX * deltaTime;
		y += velY * deltaTime;

		// 3. animeの更新


		// 4. 画面外判定
		if (x < -SAFE_MARGIN || x > 1920 + SAFE_MARGIN ||
			y < -SAFE_MARGIN || y > 1080 + SAFE_MARGIN)//シーンの幅と高さを入れる
		{
			// 画面外に出たらゲームオーバー処理へ移行
			state = STATE_GAMEOVER;
			new GameOver();
		}
	}
	if(state == STATE_GAMEOVER){
		// ゲームオーバー状態の処理（必要に応じて追加）
		boomFrame = (boomFrame + 1) % BOOM_ANIM_FRAME_INTERVAL;
		if (boomFrame == 0 && Boomtime < 36 )
		{
			boomAnimIndex = (boomAnimIndex + 1) % BOOM_ANIM_FRAME_COUNT;
			Boomtime++;
		}
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
	int boomXRect = (boomAnimIndex % BOOM_ATLAS_WIDTH) * BOOM_CHARACTER_WIDTH;
	int boomYRect = (boomAnimIndex / BOOM_ATLAS_WIDTH) * BOOM_CHARACTER_HEIGHT;
	int boomDestx = boomXRect * 2;
	int boomDesty = boomYRect * 2;
	int boomDestWidth = 64 * 2;
	int boomDestHeight = 64 * 2;

	//  キャラクターをTextureAtlasを使って表示する
	if (state == STATE_GAMEOVER) {
		int size = 10;
		double rad = 0;
		int displayX = x;
		int displayY = y;
		if (x < -SAFE_MARGIN)
		{
			rad = M_PI;
			displayX = x + (size + 1) * 32;
		}
		else if (x > 1920 + SAFE_MARGIN) {
			rad = 0;
			displayX = x - (size + 1) * 32;
		}
		else if (y < -SAFE_MARGIN) {
			rad = -M_PI / 2;
			displayY = y + (size + 1) * 32;
		}
		else if (y > 1080 + SAFE_MARGIN) {
			rad = M_PI / 2;
			displayY = y - (size + 1) * 32;
		}
		DrawRotaGraph(displayX, displayY, size, rad, boomGraphs[boomAnimIndex], TRUE,FALSE);
		//new GameOver();
	}
	else {
		DrawRectGraph(x, y, xRect, yRect, CHARACTER_WIDTH, CHARACTER_HEIGHT, animImage, TRUE, direction);
		/*int rad = M_PI;
		int size = 10;
		DrawRotaGraph(x , y, size, M_PI / 2, boomGraphs[boomAnimIndex], TRUE, FALSE);*/
		//DrawRotaGraph(x+32, y+32, 3.f, 3.14, boomGraphs[10], TRUE);
	}
	// デバッグ用情報表示
	DrawFormatString(0, 100, GetColor(255, 255, 255), "X::%4f", x);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "y::%4f", y);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "jumpcount::%d", jumpcount);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "PlayerHP::%d", PlayerHP);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "PlayerState::%d", state);
	DrawFormatString(0, 260, GetColor(255, 255, 255), "Boomtime::%d", Boomtime);


	// デバッグ用当たり判定表示
	DrawCircle(GetColliderLeftTop().x, GetColliderLeftTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderLeftBottom().x, GetColliderLeftBottom().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightTop().x, GetColliderRightTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightBottom().x, GetColliderRightBottom().y, 2, GetColor(0, 255, 0), true);
}

void Player::Move(int vx, int vy)
{
	x += vx;
	y += vy;
}

void Player::MoveSpeed(int s)
{
	speed = s;
}

void Player::VerocityUp()
{
	Gravity = -0.2;
}

void Player::VerocityDown()
{
	Gravity = 0.4;
}

void Player::VerocitySITA()
{
	Gravity = 0.01;
}
