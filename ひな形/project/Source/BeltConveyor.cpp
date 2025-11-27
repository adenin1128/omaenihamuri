#include "BeltConveyor.h"
#include "field.h"
#include "Player.h"

BeltConveyor::BeltConveyor(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/bird.png");
	x = px;
	y = py;
}

BeltConveyor::~BeltConveyor()
{
}

void BeltConveyor::Update()
{
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	int speed = 0;
	if (field->GetBeltHit() == 23) {
		speed = 2;
		player->MoveSpeed(speed);
		speed = 0;
		return;
	}
	if (field->GetBeltHit() == 24) {
		speed = -2;
		player->MoveSpeed(speed);
		speed = 0;
		return;
	}
	speed = 0;
	return;
}

void BeltConveyor::Draw()
{
	DrawGraph(x, y, ConveyorImage, TRUE);
}