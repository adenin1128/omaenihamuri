#pragma once
#include "../Library/GameObject.h"

class Box : public GameObject {
public:
	Box(int px, int py, int i);
	~Box();
	void Update() override;
	void Draw() override;

private:

	
};
