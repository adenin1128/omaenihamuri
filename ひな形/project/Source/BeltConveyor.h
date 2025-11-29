#pragma once
#include "../Library/GameObject.h"

class BeltConveyor : public GameObject
{
public:
	BeltConveyor(int px, int py);
	~BeltConveyor();
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