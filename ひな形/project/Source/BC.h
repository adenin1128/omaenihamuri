#pragma once
#include "../Library/GameObject.h"

class BC : public GameObject
{
public:
	BC(int px, int py);
	~BC();
	void Update() override;
	void Draw() override;
	int GetSpeed() { return speed; }
private:
	int ConveyorImage;
	int x, y;
	int speed;
	int timer;
	int frame;
	int hanten;
};