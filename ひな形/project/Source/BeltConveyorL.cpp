#include "BeltConveyorL.h"
#include "field.h"
#include "Player.h"

BeltConveyorL::BeltConveyorL(int px, int py)
{
	ConveyorImage = LoadGraph("data/image/bird.png");
	x = px;
	y = py;
	speed = 0;
}

BeltConveyorL::~BeltConveyorL()
{
}

void BeltConveyorL::Update()
{
	Field* field = FindGameObject<Field>();
	Player* player = FindGameObject<Player>();
	if (field->GetBeltHit() == 24) {
		speed = -5;
	}
	else {
		speed = 0;
	}
	return;
}

void BeltConveyorL::Draw()
{
	DrawGraph(x, y + 64, ConveyorImage, TRUE);
}