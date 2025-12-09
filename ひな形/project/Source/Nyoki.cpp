#include "nyoki.h"
#include "field.h"
#include "Player.h"
#include <assert.h>
#include "CsvReader.h"
#include <vector>
#include <cmath>

using namespace std;

int NyokiGraphs[5];
int blockImage;
float moveX;
int moveCount;

Nyoki::Nyoki(int px, int py, int mx, int count)
{
	blockImage = LoadGraph("data/image/New blo.png");
	//nyokiImage = LoadGraph("data/image/nyoblo.png");
	//LoadDivGraph("data/image/nyoblo.png", 5, 5, 1, 64, 64 * 4, NyokiGraphs);
	assert(blockImage > 0);
	resetX = px;
	resetY = py;
	moveX = mx;
	moveCount = count;
	Reset();
}

Nyoki::~Nyoki()
{
	DeleteGraph(nyokiImage);
}

void Nyoki::Reset()
{
	state = STATE_NEW;
	nx = resetX;
	ny = resetY;
	size = 64;
	move = 0;
	count = 0;
	loop = 4;//4にしたらニョキニョキする
	a = false;

	currentMoveX = 0;
	maxMoveX = 0;
	nyokiSpeed = 3;

}

void Nyoki::MoveOneStep(float dir)
{
	const float dx = nyokiSpeed * dir;

	// 残距離に合わせて丸める（行き過ぎ防止）
	const float remaining = fabs(maxMoveX) - currentMoveX;
	float step = dx;
	if (fabs(dx) > remaining) {
		step = (dx > 0 ? +remaining : -remaining);
	}

	// 床移動
	nx += step;
	currentMoveX += fabs(step);
}

void Nyoki::Update()
{
	Field* field = FindGameObject<Field>();
	if (CheckHitKey(KEY_INPUT_R)) {
		DestroyMe();
		return;
	}

	//maxMoveX = field->NyokiMove(nx, ny);
	//if (maxMoveX == 0.0f)return;

	switch (state) {
	case STATE_NEW: {
		if (loop > 0) {
			count++;
			if (count % 10 == 0) {
				count = 0;
				move++;
				loop--;
				if (move >= 4) {
					move = 4;
				}
			}
		}
		if (loop == 0) {
			state = STATE_MOVE1;
		}
		break;
	}
	case STATE_MOVE1: {
		if (moveCount == 0) break;
		if (moveCount % 2 == 0) {
			float deltaMoveX = moveX / nyokiSpeed * Time::DeltaTime();
			currentMoveX += deltaMoveX;
			nx += deltaMoveX;
		}
		else{
			float deltaMoveX = moveX / nyokiSpeed * Time::DeltaTime();
			currentMoveX += deltaMoveX;
			nx -= deltaMoveX;
		}
		
		if (abs(currentMoveX) >= abs(moveX)) {
			if (moveCount % 2 == 0) {
				nx = resetX + moveX;
			}
			else {
				nx = resetX;
			}
			moveCount -= 1;
			currentMoveX = 0;
		}
		break;
	}
	
	case STATE_STOP: {
		break;
	}
	default:
		break;
	}
}

void Nyoki::Draw()
{
	/*if (loop > 0) {
		count += 1;
		if (count >= 10) {
			count = 0;
			move = (move + 4) % 17;
			loop--;
		}
		DrawRectGraph(nx, ny, size* move, 0, size, size * 4, nyokiImage, TRUE);
	}*/
	for (int i = 0; i < move; i++) {
		DrawGraph(nx, ny + i * 64, blockImage, TRUE);
	}
	//DrawRotaGraph(nx * 64, ny * 64, 1, 0, NyokiGraphs[move], TRUE, FALSE);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "loop:: %d", loop);
}

// プレイヤーの下判定用
int Nyoki::HitCheckDown(int px, int py) {
	// Nyokiの横範囲内かチェック
	if (px < nx || px >= nx + size) return 0;

	// ブロックの上面とプレイヤーの足元の距離
	int push = py - ny;
	if (push >= 0 && push < 16) {  // ブロックの上面付近なら押し出す
		return push;
	}
	return 0;
}

// プレイヤーの横判定用（右に移動するとき）
int Nyoki::HitCheckRight(int px, int py) {
	// Nyokiの縦範囲内かチェック
	if (py < ny || py >= ny + 256) return 0;

	// プレイヤーの右端がNyokiの左端に当たったか
	int push = nx - px;
	if (push < 0 && push > -16) {
		return -push;  // 正の値で返す
	}
	return 0;
}

// プレイヤーの横判定用（左に移動するとき）
int Nyoki::HitCheckLeft(int px, int py) {
	// Nyokiの縦範囲内かチェック
	if (py < ny || py >= ny + 256) return 0;

	// プレイヤーの左端がNyokiの右端に当たったか
	int push = (nx + 64) - px;
	if (push > 0 && push < 16) {
		return -push;  // 負の値で返す
	}
	return 0;
}

// プレイヤーの上判定用
int Nyoki::HitCheckUp(int px, int py) {
	// Nyokiの横範囲内かチェック
	if (px < nx || px >= nx + 64) return 0;

	// プレイヤーの頭がNyokiの下面に当たったか
	int push = (ny + 256) - py;
	if (push > 0 && push < 16) {
		return push;
	}
	return 0;
}