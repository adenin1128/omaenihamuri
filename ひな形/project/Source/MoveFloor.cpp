#include "MoveFloor.h"
#include "Player.h"
#include "field.h"
#include <assert.h>


MoveFloor::MoveFloor(int px, int py)
{
	fImage = LoadGraph("data/image/chara.png");
	assert(fImage > 0);
	x = px;
	y = py;
	RightSpeed = -3.0f;
	LeftSpeed = 3.0f;
	MaxMoveFloor = 0.0;
	currentMoveFloor = 0.0;
	state = STATE_A;
}

MoveFloor::~MoveFloor()
{
}

void MoveFloor::Update()
{
	Field* field = FindGameObject<Field>();
	if (state == STATE_A) {
		MaxMoveFloor = field->Movefloor(x, y);
		if (currentMoveFloor < MaxMoveFloor) {
			currentMoveFloor++;
			x += LeftSpeed;
		}
		if (currentMoveFloor > MaxMoveFloor) {
			currentMoveFloor++;
			x += RightSpeed;
		}
	}
	if (field->GetHit() == true) {
		state = STATE_B;
	}
	if (state == STATE_B) {
		MaxMoveFloor = field->Movefloor(x, y);
		if (currentMoveFloor < MaxMoveFloor) {
			currentMoveFloor++;
			x += LeftSpeed;
		}
		if (currentMoveFloor > MaxMoveFloor) {
			currentMoveFloor++;
			x += RightSpeed;
		}
	}
	if (field->GetHita() == true) {
		state = STATE_C;
	}
	if (state == STATE_C) {
		MaxMoveFloor = field->Movefloor(x, y);
		if (currentMoveFloor < MaxMoveFloor) {
			currentMoveFloor++;
			x += LeftSpeed;
		}
		if (currentMoveFloor > MaxMoveFloor) {
			currentMoveFloor++;
			x += RightSpeed;
		}
	}
}



void MoveFloor::Draw()
{
	DrawGraph(x, y, fImage, 1);
}