#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

class Field : public GameObject
{
public:
	Field();
	~Field();
	void Update() override;
	void Draw() override;

	int HitCheckRight(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckDown(int px, int py);
	int GetScrollX() { return scrollX; }
	void SetScrollX(int s) { scrollX = s; }
	bool Istrap(int px, int py);
	int HitCheckRightTrap(int px, int py);
	int HitCheckLeftTrap(int px, int py);
	int HitCheckUpTrap(int px, int py);
	int HitCheckDownTrap(int px, int py);
private:
	int hImage;
	float x, y;
	int scrollX;
	int harimage;
	int hataimage;
	int haikeimage;
	int HIT_TRAP = 0;
};