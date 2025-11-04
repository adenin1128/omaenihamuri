#include "player.h"
#include "Field.h"
#include "DxLib.h"
#include "Trigger.h"
#include "Gameover.h"
#include "trap.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define PI    3.1415926535897932384626433832795f

static const float Gravity = 0.4;
static const float v0 = -10.0;

const float DRAG_COEFFICIENT = 0.05f;  // 速度の減衰係数
const float ROT_SPEED = 0.0f;          // 回転速度
const int SAFE_MARGIN = 100;           // 画面外判定マージン

int boomGraphs[36];


Player::Player(float startX, float startY)
	: x(startX), y(startY), velocity(0.0f), onGround(false)
{
	animImage = LoadGraph("data/image/おまえ歩き.png");
	BOOMImage = LoadGraph("data/image/BOOM!!.png");
	LoadDivGraph("data/image/BOOM!!.png", 36, 36, 1, 64, 64, boomGraphs);
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
	if (state == STATE_NORMAL) {
		int moveX = 0;

		if (PlayerHP == 0) {
			new GameOver();
		}
		if (CheckHitKey(KEY_INPUT_R))
		{
			PlayerHP = 3;
		}
		if (onGround == true) {
			if (jumpcount < Maxjumpcount) {
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
	if (state == STATE_BOOM) {

		const float deltaTime = 50.0f / 60.0f;

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
			new GameOver(); // ここで初めてゲームオーバー画面へ移行するようにしたい
		}
	}
	if(state == STATE_GAMEOVER){
		// ゲームオーバー状態の処理（必要に応じて追加）
		boomFrame = (boomFrame + 1) % BOOM_ANIM_FRAME_INTERVAL;
		if (boomFrame == 0)
		{
			boomAnimIndex = (boomAnimIndex + 1) % BOOM_ANIM_FRAME_COUNT;
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
			rad = PI / 2;
			displayY = y - (size + 1) * 32;
		}
		DrawRotaGraph(displayX, displayY, size, rad, boomGraphs[boomAnimIndex], TRUE,FALSE);
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


	// デバッグ用当たり判定表示
	DrawCircle(GetColliderLeftTop().x, GetColliderLeftTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderLeftBottom().x, GetColliderLeftBottom().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightTop().x, GetColliderRightTop().y, 2, GetColor(0, 255, 0), true);
	DrawCircle(GetColliderRightBottom().x, GetColliderRightBottom().y, 2, GetColor(0, 255, 0), true);
}
