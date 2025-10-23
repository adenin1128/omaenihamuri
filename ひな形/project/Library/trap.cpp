#include "trap.h"
#include "field.h"
#include "Player.h"

trap::trap(int px,int py)
{
	hariImage = LoadGraph("data/image/hari.png");
	x = px;
	y = py;
	UP = -1.0f;
}

trap::~trap()
{
}

void trap::Update()
{

	y += UP;
}

void trap::Draw()
{
	DrawGraph(x, y, hariImage, true);
}