#pragma once
#include "../Library/GameObject.h"

class Skeleton : public GameObject
{
public:
	Skeleton(int px, int py);
	~Skeleton();
	void Update() override;
	void Draw() override;
	bool IsHit(int px, int py);
private:
	float x, y;
	int size;
	int b;
};