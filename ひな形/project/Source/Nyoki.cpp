#include "nyoki.h"
#include "field.h"
#include "Player.h"
#include <assert.h>
#include "CsvReader.h"
#include <vector>

//vector<vector<int>> maps;

Nyoki::Nyoki(int px, int py)
{
	nyokiImage = LoadGraph("data/image/nyoblo.png");
	assert(nyokiImage > 0);
	nx = px;
	ny = py;
	size = 64;
	move = 0;
	count = 0;
	loop = 4;//4にしたらニョキニョキする
	a = false;
	currentMoveX = 0;
	maxMoveX = 0;
}

Nyoki::~Nyoki()
{
}

void Nyoki::Update()
{
	Field* field = FindGameObject<Field>();
	if (CheckHitKey(KEY_INPUT_R)) {
		DestroyMe();
		return;
	}
	if (loop > 0) {
		count += 1;
		if (count >= 10) {
			count = 0;
			move = (move + 4) % 17;
			loop--;
		}
	}
	if (loop == 0) {
		Field* field = FindGameObject<Field>();
		maxMoveX = field->NyokiStop();
		if (currentMoveX < maxMoveX) {
			currentMoveX += 10;
			nx += 10;
		}
		if (currentMoveX > maxMoveX) {
			currentMoveX -= 10;
			nx -= 10;
		}
	}
}

void Nyoki::Draw()
{
	DrawRectGraph(nx, ny, size * move, 0, size, size * 4, nyokiImage, TRUE);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "count:: %d", count);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "move:: %d", move);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "loop:: %d", loop);
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