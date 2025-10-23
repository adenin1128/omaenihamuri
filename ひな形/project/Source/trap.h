#pragma once
#include "../Library/GameObject.h"

class trap : public GameObject {
public:
	trap(int px, int py);
	~trap();
	void Update() override;
	void Draw() override;
private:
	int hariImage;
	float x, y;
	float UP;
};
