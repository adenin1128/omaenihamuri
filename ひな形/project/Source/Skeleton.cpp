#include "Skeleton.h"
#include "field.h"
#include "Player.h"

Skeleton::Skeleton(int px, int py)
{
	Image = LoadGraph("data/image/bird.png");
	ResetX = px;
	ResetY = py;
}

Skeleton::~Skeleton()
{
}

void Skeleton::Reset()
{
	x = ResetX;
	y = ResetY;
	size = 64;
}

void Skeleton::Update()
{
}

void Skeleton::Draw()
{
	DrawGraph(x, y, Image, TRUE);
}

// プレイヤーの下判定用
int Skeleton::HitCheckDown(int px, int py) {
	// Skeletonの横範囲内かチェック
	if (px < x || px >= x + size) return 0;

	// ブロックの上面とプレイヤーの足元の距離
	int push = py - y;
	if (push >= 0 && push < 16) {  // ブロックの上面付近なら押し出す
		return push;
	}
	return 0;
}

// プレイヤーの横判定用（右に移動するとき）
int Skeleton::HitCheckRight(int px, int py) {
	// Skeletonの縦範囲内かチェック
	if (py < y || py >= y + size) return 0;

	// プレイヤーの右端がSkeletonの左端に当たったか
	int push = x - px;
	if (push < 0 && push > -16) {
		return -push;  // 正の値で返す
	}
	return 0;
}

// プレイヤーの横判定用（左に移動するとき）
int Skeleton::HitCheckLeft(int px, int py) {
	// Skeletonの縦範囲内かチェック
	if (py < y || py >= y + size) return 0;

	// プレイヤーの左端がSkeletonの右端に当たったか
	int push = (x + 64) - px;
	if (push > 0 && push < 16) {
		return -push;  // 負の値で返す
	}
	return 0;
}

// プレイヤーの上判定用
int Skeleton::HitCheckUp(int px, int py) {
	// Skeletonの横範囲内かチェック
	if (px < x || px >= x + 64) return 0;

	// プレイヤーの頭がSkeletonの下面に当たったか
	int push = (y + size) - py;
	if (push > 0 && push < 16) {
		return push;
	}
	return 0;
}