#pragma once
#include "../Library/GameObject.h"
#include "Breath.h"
#include <cstdlib>
#include <cmath>
#include "Player.h"
#include "StageNumber.h"


class Boaaa : public GameObject {

public:
	Boaaa(int px, int py);
	~Boaaa();
	void Update() override;
	void Draw() override;
	bool CheckHit(Player* player);
private:
	int boaimage;
	int x, y;
	int frame3;
	int timer3;
	int length;
	int color;
	int baseThickness;
	int changeThickness;
	int thickness;
	int bx, by;
	int buretimer;
};