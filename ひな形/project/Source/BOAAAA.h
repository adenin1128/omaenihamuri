#pragma once
#include "../Library/GameObject.h"
#include "Breath.h"

class Boaaa : public GameObject {

public:
	Boaaa(int px, int py);
	~Boaaa();
	void Update() override;
	void Draw() override;
private:
	int boaimage;
	int x, y;
	int frame3;
	int timer3;
};