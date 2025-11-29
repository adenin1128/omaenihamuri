#pragma once
#include "../Library/GameObject.h"

class Skeleton : public GameObject
{
public:
	Skeleton(int px, int py);
	~Skeleton();
	void Update() override;
	void Draw() override;

	int HitCheckDown(int px, int py);
	int HitCheckLeft(int px, int py);
	int HitCheckUp(int px, int py);
	int HitCheckRight(int px, int py);

private:
	float x, y;
	int size;
};