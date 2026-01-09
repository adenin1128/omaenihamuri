#pragma once
#include "../Library/GameObject.h"
#include "Breath.h"
#include <cstdlib>
#include <cmath>
#include "Player.h"
#include "StageNumber.h"

class Boaaa : public GameObject {
public:
	Boaaa(int px, int py, int dir, int length);
	~Boaaa();
	void Update() override;
	void Draw() override;
	bool CheckHit(Player* player);
	enum Direction {
		TOP,  //0
		RIGHT,//1
		UNDER,//2
		LEFT  //3
	};
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
	Direction dir;
	double rot;
};