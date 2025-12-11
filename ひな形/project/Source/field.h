#pragma once
#include "../Library/GameObject.h"
#include "Skeleton.h"
#include "Player.h"
#include <vector>
#include <memory>

enum ClearState {
	STATE_0,    // ドア待機状態
	STATE_1,    // ドア閉めてる
	STATE_2     // ドア閉まってる状態
};

class Field : public GameObject
{
public:
	Field(int stage);
	~Field();
	void Update() override;
	void Draw() override;

	void CheckTrap(int x, int y);
	int HitCheckRight(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckDown(int px, int py);
	int GetScrollX() { return scrollX; }
	void SetScrollX(int s) { scrollX = s; }
	bool OutOfMap(int px, int py);
	bool Istrap(int px, int py);
	bool IsGoal(int px, int py);
	int NyokiMove(int px, int py);
	bool IsSkeleton(int px, int py);
	bool Jetpack(int px, int py);
	bool IsGate(int px, int py);
	int IsBelt(int px, int py);
	int Movefloor(int px, int py);
	int IsBreath(int px, int py);
	// 指定した番号(id)の座標を ox, oy に入れて返す関数
	bool GetPointPos(int id, int* ox, int* oy);
	/*int HitCheckRightTrap(int px, int py);
	int HitCheckLeftTrap(int px, int py);
	int HitCheckUpTrap(int px, int py);
	int HitCheckDownTrap(int px, int py);*/
	void ChangeMapChip(int x, int y, int type);
	void ChangeRespawnPoint(int x, int y);
	void ChangeClearPoint(int x, int y);
	int GetDeathCount() { return deathcount; }
	int GetBeltHit() { return BeltHit; }
	ClearState state;
	ClearState GetState() const { return state; }
	void SetState(ClearState s) { state = s; }
	void SetClear() {
		state = STATE_1;
	}

	int GetJetpack() { return jet; }
	int GetGateHit() { return DL; }
	bool GetHit() { return one; }
	bool GetHita() { return two; }
private:
	std::vector<std::unique_ptr<Skeleton>> skeletons;
	int hImage;
	float x, y;
	int scrollX;
	int harimage;
	int hataimage;
	int haikeimage;
	int harisitaimage;
	int doorimage;
	int kaiheiimage;
	int gokunobanImage;
	int fImage;
	int HIT_TRAP = 0;
	int deathcount;
	bool clear;
	int size;
	int timer;
	int frame[6];
	int hit;
	bool jet;
	int easyImage;
	int HGimage;
	int DL;
	int BeltHit;
	bool skHit;
	bool one;
	bool two;
};