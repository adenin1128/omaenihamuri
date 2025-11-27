#include "BeltConveyor.h"
#include "field.h"
#include "Player.h"

BeltConveyor::BeltConveyor(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/bird.png");
	x = px;
	y = py;
	speed = 0;
}

BeltConveyor::~BeltConveyor()
{
}

void BeltConveyor::Update()
{
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	if (field->GetBeltHit() == 23) {
		speed = 5;
	}
	else if (field->GetBeltHit() == 24) {
		speed = -5;
	}
	else {
		speed = 0;
	}
	return;
}

void BeltConveyor::Draw()
{
	DrawGraph(x, y + 64, ConveyorImage, TRUE);
}