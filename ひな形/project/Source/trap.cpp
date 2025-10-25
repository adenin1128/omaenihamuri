#include "trap.h"
#include "field.h"
#include "Player.h"

trap::trap(int px,int py, int i)
{
	type = (Type)i;
	hariImage = LoadGraph("data/image/hari.png");
	x = px;
	y = py;
	UP = -1.0f;
	isActive = false;
}

trap::~trap()
{
}

void trap::Update()
{
	
	if (isActive == true) {
		switch (type) {
		case Up:
			y += UP;
			break;
		case Down:
			y -= UP;
			break;
		}
	}
}

void trap::Active() {
	isActive = true; 
}

void trap::Draw()
{
	DrawGraph(x, y, hariImage, true);
}