#pragma once
#include "../Library/GameObject.h"

class BeltConveyor : public GameObject
{
public:
	BeltConveyor(int px, int py);
	~BeltConveyor();
	void Update() override;
	void Draw() override;
private:
	int ConveyorImage;
	int x, y;
};