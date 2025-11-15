#pragma once
#include "../Library/GameObject.h"

class Gravity : public GameObject
{
public:
	Gravity(int px, int py);
	~Gravity();
	void Update() override;
	void Draw() override;
	bool isDown(int px, int py);

private:
	float gx, gy;
	int size;
};