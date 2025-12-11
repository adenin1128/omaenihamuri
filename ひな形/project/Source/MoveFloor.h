#pragma once
#include "../Library/GameObject.h"

enum MoveFloorState {
	STATE_A,    // 30 -> 31（初期：乗ったら動作開始）
	STATE_B,    // 31 -> 32（自動継続）
	STATE_C,    // 32 -> 33 (31から33へ移動)
	STATE_D     // 33 -> 31（折り返し）
};

class Player; // 前方宣言

class MoveFloor : public GameObject {
public:
	MoveFloor(int px, int py);
	~MoveFloor();
	void Update() override;
	void Draw() override;
	void Reset();

	int HitCheckDown(int px, int py);

	MoveFloorState GetState() const { return state; }
	void SetState(MoveFloorState s) { state = s; }

private:
	int frame;
	int timer;

	// 座標・描画
	int resetX, resetY;
	float x, y;
	int   fImage;
	int size;

	// 速度
	float moveSpeed;          // px/フレーム

	// ★削除：2D移動方式（座標ターゲット方式）に変えたため、以下の距離管理変数は不要です
	// float maxSegmentLength;
	// float progressed;

	// 状態
	MoveFloorState state;
	bool activatedA;          // STATE_Aで「乗って動作開始した」フラグ

	// 床サイズ（当たり判定用）
	static constexpr int PLATFORM_W = 64;
	static constexpr int PLATFORM_H = 16;

	// ユーティリティ
	bool IsPlayerOn(const Player* p) const;

	// ★変更：XとYそれぞれの移動量を受け取る形に修正
	void MoveOneStep(float moveX, float moveY, Player* p);
};