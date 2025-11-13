#pragma once
#include "../Library/GameObject.h"

class Field : public GameObject
{
public:
	Field(int stage);
	~Field();
	void Update() override;
	void Draw() override;

	int HitCheckRight(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckDown(int px, int py);
	int GetScollX() { return scrollX; }
	void SetScrollX(int s) { scrollX = s; }
	bool OutOfMap(int px, int py);
	bool IsGoal(int px, int py);
private:
	int hImage;
	float x, y;
	int scrollX;
};