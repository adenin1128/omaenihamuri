#pragma once
#include "../Library/GameObject.h"

class BeltConveyorL : public GameObject
{
public:
	BeltConveyorL(int px, int py);
	~BeltConveyorL();
	void Update() override;
	void Draw() override;
	int GetSpeed() { return speed; }
private:
	int ConveyorImage;
	int x, y;
	int speed;
	int timer;
	int frame;
};