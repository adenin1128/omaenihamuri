#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

class Field : public GameObject
{
public:
	Field(int stage);
	~Field();
	void Update() override;
	void Draw() override;

	void CheckTrap(int x, int y);
	void Checkbol(int x, int y);
	int HitCheckRight(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckDown(int px, int py);
	int GetScrollX() { return scrollX; }
	void SetScrollX(int s) { scrollX = s; }
	bool OutOfMap(int px, int py);
	bool Istrap(int px, int py);
	bool IsGoal(int px, int py);
	/*int HitCheckRightTrap(int px, int py);
	int HitCheckLeftTrap(int px, int py);
	int HitCheckUpTrap(int px, int py);
	int HitCheckDownTrap(int px, int py);*/
	void ChangeMapChip(int x, int y, int type);
	void ChangeRespawnPoint(int x, int y);
	void ChangeClearPoint(int x, int y);
	int GetDeathCount() { return deathcount; }
private:
	int hImage;
	float x, y;
	int scrollX;
	int harimage;
	int hataimage;
	int haikeimage;
	int harisitaimage;
	int doorimage;
	int HIT_TRAP = 0;
	int deathcount;
	bool clear;
	int size;
};