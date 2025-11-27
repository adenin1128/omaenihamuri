#include "MoveFloor.h"
#include "Player.h"

MoveFloor::MoveFloor(int px, int py)
{
}

MoveFloor::MoveFloor(int px, int py, int i)
{
	fImage = LoadGraph("data/image/New blo.png");
	x = 500;
	y = 200;
	RightSpeed -= 3.0f;
	//LeftSpeed += 3.0f;
}

MoveFloor::~MoveFloor()
{
}

void MoveFloor::Update()
{
	for (;;)
	{
		RightSpeed;
	}
}

int MoveFloor::HitCheckRight(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	return 0;
}

int MoveFloor::HitCheckLeft(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	return 0;
}

int MoveFloor::HitCheckUp(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	return 0;
}

int MoveFloor::HitCheckDown(int px, int py)
{
	int x = px / 64;
	int y = py / 64;
	return 0;
}


void MoveFloor::Draw()
{
	DrawGraph(x, y, fImage, true);

}