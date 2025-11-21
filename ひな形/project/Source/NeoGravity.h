#pragma once
#include "../Library/GameObject.h"

class NeoGravity : public GameObject
{
public:
	NeoGravity(int px, int py);
	~NeoGravity();
	void Update() override;
	void Draw() override;
	bool isUp(int px, int py);

private:
	float gx, gy;
	int size;
};
