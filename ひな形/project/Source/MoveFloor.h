#pragma once
#include "../Library/GameObject.h"

class MoveFloor : public GameObject {
public:
	MoveFloor(int px, int py);
	MoveFloor(int px, int py, int i);
	~MoveFloor();
	void Update() override;
	int HitCheckRight(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckDown(int px, int py);
	void Draw() override;

private:
	float x, y;
	float Mx, My;
	float RightSpeed;
	float LeftSpeed;
	int fImage;

};
